# Django Class based view

- Django 프로젝트를 수행하면서 조사한 정보 정리

- 참고 사이트 : http://ruaa.me/django-view/
  

### Generic views

```python
from django.views.generic import ListView, TemplateView #다양한 generic View가 있음
from django.contib.auth.views import PasswordChangeView
```

- django에 기본으로 저장되어 있는 class based view
- Generic view 마다 전달해야 되는 parameter의 성격이 다르니 오른쪽 클릭 -> find usage로 필요한 정보를 확인



### Function

- Generic view에 기본적으로 정의되어 있는 함수.

- view, 특히 Generic Views를 상속받아서 작업할 때 원하는 결과를 뽑기 위해 기능을 override 해서 사용해야 한다.

  

#### get_queryset()

- DB에서 데이터를 가져오는 역할을 하는 함수

- 굳이 정의하지 않아도 generic view 에서 model parameter을 입력할 경우 자동으로 모델 데이터를 가져온다.

  ```python
  class MyOrderView(LoginRequiredMixin,ListView):
      template_name = "mypage/mypage_order.html"
      
      
      model = Order   
      #  model = Order는 
      #  def get_queryset(self): 
      #		return Order.objects.all()
      #  코드와 동일한 결과를 낸다. 
      
      context_object_name = "order"
      paginate_by = 3
      def get_queryset(self):
          return 	Order.objects.filter(user_id=self.request.user.pk).select_related("product_id")
      # 지금 로그인한 유저의 주문 내역을 가져온다. 
      # Order 테이블에는 user_id와 product_id 외래키가 존재하므로 
      # 상세 정보를 얻기 위해 Join 한 결과를 반환
  	# 장고 템플릿에서 그냥 related object를 뽑아도 된다. 
  ```

  

#### get_context_data()

- 템플릿에서 사용할 context 변수명을 정의한다. 

  ```python
  class UserCreateDoneTV(TemplateView):
      template_name = 'registration/register_done.html'
      def get_context_data(self, **kwargs):
          context = {}
          context['nice_uid'] = self.request.session.get('success_id')
          context['nice_name'] = self.request.session.get('success_name')
          context['nice_email'] = self.request.session.get('success_email')
          return context
  ```

- 이 경우, template에서는 이렇게 사용할 수 있다.

  ```HTML
  <ul>
     <li>
        <strong class="bolds">아이디</strong><span><span>{{nice_uid}}</span></span>
     </li>
     <li>
        <strong class="bolds">이름</strong><span><span>{{nice_name}}</span></span>
     </li>
     <li>
        <strong class="bolds">이메일</strong><span><span>{{nice_email}}</span></span>
     </li>
  </ul>
  ```

  

- model data를 받아올 경우, 상속받은 클래스에서 context data를 처리해주므로 상위 클래스의 context를 받아와야 한다.

  ```python
  class PostLV(TemplateView):
      template_name = 'blog/post_all.html'
      model = Post
      context_object_name = 'pooost'   
      # 상속받은 Template에서 model context명을 자동으로 처리하므로
      # 다른 이름을 사용하려면
      # context_object_name을 설정해야 한다.
      
      def get_context_data(self, **kwargs):
          context = super(PostLV,self).get_context_data(**kwargs)
          context['context_one'] = str('첫 번째 컨텍스트 추가요')
          context['context_two'] = str('한 그릇 더')
          context['context_three'] = str('마지막 한조 각까지')
          return context
  ```

- template 예시

  ```HTML
  {%for post in pooost%}
      <h3><a href="{{post.get_absolute_url}}">{{post.title}}</a></h3>
      	{{post.modify_dt|date:"N d, Y"}}<br>작성자 : {{post.owner}}<br>조회수 : {{post.read_cnt}}
      <p>{{post.description}}</p>
      {{object.content | safe}}
  {% endfor %}
  ```

  

#### get_form()

- 정의된 model form을 가져온다. 이 과정에서 초기값 등을 설정할 수 있음

  ```python
  class ModifyUserView(LoginRequiredMixin, FormView):
      template_name = "mypage/mypage_modify_user.html"
      
      
      form_class = UserChangeForm
      #form_class에 정의된 form을 View에서 보여준다.
      
      success_url = reverse_lazy('mypage:mypage_index')
  
      def get_form(self):
          form = super(ModifyUserView, self).get_form()
          # form의 addr, phone, birthdate 필드의 값을 현재 유저의 정보로 설정한다.
          form.fields['addr'].widget.attrs.update({'value': self.request.user.addr})
          form.fields['phone'].widget.attrs.update({'value': self.request.user.phone})
          form.fields['birthdate'].widget.attrs.update({'value': self.request.user.birthdate})
          return form
  
      def form_valid(self, form):
          response = super().form_valid(form)
          Users = self.request.user
          Users.addr = form.instance.addr
          Users.birthdate = form.instance.birthdate
          Users.phone = form.instance.phone
          Users.save()
          return response
  ```



#### form_valid()

- 유효한 정보(cleaned_data)가 입력된 form이 <u>**POST 될 경우**</u> 호출되는 로직이다.

- 정의된 generic view에서는 기본적으로 success_url에 등록된 url로 redirect한다. 

- override할 경우, render을 쓰든 super을 받아 쓰든 반드시 **HttpResponse**를 반환해야 한다. 

- 일반적으로 이 작업은 generic view에 정의되어 있으므로 수동으로 response를 정의하지 않을 경우 super로 갖다 쓰는 것을 추천	

- 기타 데이터 저장/처리같은 것을 여기서 실행하게 된다.

  ##### 예제 1

  ```python
  class PostCreateView(LoginRequiredMixin, CreateView):
      model = Post
      fields = ['title', 'slug', 'description', 'content', 'tags']
      initial = {'slug': 'auto-filling-do-not-input'}
      success_url = reverse_lazy('blog:index')
  
      def form_valid(self, form):
          #form_field에서 5가지 정보만 받았으므로 Post를 만들기 위해 나머지를 채워넣는다. 
          form.instance.owner = self.request.user
          form.instance.modify_dt = timezone.now()
                 
          # 데이터 저장 작업 로직 자체는 CreateView의 form_valid에서 실행하므로 super로 불러온다.
          response = super().form_valid(form)
          
          # 올라간 파일은 PostAttachfile로 self.object와 다르기 때문에 CreateView에서 저장이 안 됨.
          # 따라서 이 클래스의 form_valid에서 따로 저장한다. 
          files = self.request.FILES.getlist("files")
          for file in files:
              attach_file = PostAttachFile(post=self.object, filename=file.name, size=file.size,
                                           content_type=file.content_type, upload_file=file)
              attach_file.save()
          return response
  ```

  ##### 예제 2

  ```python
  class SearchFormView(FormView):
      form_class = PostSearchForm
      template_name = 'blog/post_search.html'
  
      def form_valid(self, form):
          searchWord = form.cleaned_data['search_word']
          post_list = Post.objects.filter(Q(title__icontains=searchWord) |
                                          Q(description__icontains=searchWord) |
                                          Q(content__icontains=searchWord)).distinct()
          
          # 검색결과 뷰에서 쓸 context가 없으므로 따로 지정해줘야 한다.
          context = {}
          context['form'] = form
          context['search_term'] = searchWord
          context['object_list'] = post_list
  		
          # 상속받은 클래스의 form_valid를 사용하지 않고 context를 얹어서 따로 구현 
          return render(self.request, self.template_name, context)
  
  ```

  

  