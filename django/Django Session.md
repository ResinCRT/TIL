# Django Session

- settings.py에 session이 기본값으로 Install 되어있음
- import가 필요 없다. self.request.session을 view 아무 곳에서나 호출에서 사용할 수 있다.





### session 작동 원리

1. 유저가 브라우저로 사이트에 접속한다.

2. django 서버 측에서 접속한 브라우저에 sessionId를 부여한다.

    (session에 관한 변수들은 서버측에 저장) 

3. 브라우저 측에서는 쿠키에 다른 변수를 저장하지 않고 sessionId 하나만을 저장한다.

4. 서버측과 통신할 때 마다 이 sessionId를 가지고 서버가 유저들을 구분할 수 있음(비로그인 포함)





### Cookie와 session의 차이점

- session에서는 임시 정보가 서버(이 경우 django 측)에 저장된다. 하지만 cookie는 임시 정보가 사용자 컴퓨터에 쿠키 파일로 저장된다.

  



### 언제 쓰는가?

- 세션 단위로 변수를 전역으로 써야할 때 사용한다. 

- 뷰에서 다른 뷰로 데이터를 전송할 때 사용할 수 있다. 

- 비로그인 정보를 저장할 때 사용할 수 있다. 비로그인 사이트 이용, 비로그인 장바구니 등등

  



### 어떻게 쓰는가?

- 설치 확인 -> settings.py

  ```python
  INSTALLED_APPD = [
      ...
      
      'django.contrib.sessions',  #startproject할 때 자동으로 생성됨.
      
      ...
  ]
  ```

- import 할 필요 없음. self.request.session을 통해 사용 가능하다.
-  self.request가 참조 가능하면 view 어느 곳에서나 원할 때 사용할 수 있다.
- session의 정보는 dict 형태로 저장된다. 따라서 self.request.sessions[ ' key ' ] = value 형식으로 참조한다.



#### 예제

- register/views.py

  ```python
  ...
  
  class UserCreateView(CreateView):
      template_name = 'registration/register.html'
      form_class = UserCreationForm
      success_url = reverse_lazy('register:sign_up_done')
  
      def form_valid(self, form):
          response = super(UserCreateView, self).form_valid(form)
          #session에 회원가입시 form에다 입력했던 정보를 세션에 저장
          self.request.session['success_id'] = self.request.POST.get('username')
          self.request.session['success_name'] = self.request.POST.get('real_name')
          self.request.session['success_email'] = self.request.POST.get('email')
          return response
  
  
  class UserCreateDoneTV(TemplateView):
      template_name = 'registration/register_done.html'
      
      def get_context_data(self, **kwargs):
          context = {}
          #회원가입 완료 페이지에서 회원가입view에서 입력했던 session 정보를 사용
          context['username'] = self.request.session.get('success_id')
          context['real_name'] = self.request.session.get('success_name')
          context['email'] = self.request.session.get('success_email')
          return context
      
  ...
  ```

  

