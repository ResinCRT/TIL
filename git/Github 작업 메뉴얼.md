# 6조 Github 작업 메뉴얼

### 작업 내용 불러오기 



##### Pycharm 상단 메뉴바

-> VCS

-> Git/Branches



현재 작업한거 다 백업한 후

#### Remote Branches 의 origin/dev 선택 후 checkout 

성공하면 Local Branches에 dev 브랜치가 생기고 오른쪽 옆에  origin/dev라고 적혀있을거임



그 이후 new branches  누르고 원하는 이름으로 생성, 여기선 임시로 mybranch로 하겠음



##### <u>참고</u>

<u>Untracked files Prevent Checkout 오류 날 때</u>

우하단에 뜨는 팝업창에서 View Files 클릭 **or** Event Log에서 View files 클릭

->pycache 관련 파일 전부 체크 후 좌상단의 - 모양(Delete라고 써있음) 클릭 후 다시 checkout 실행



### 브랜치에서 작업하기

1. Local branch에 mybranch 가 생긴 것을 확인 (mybranch 오른쪽에 아무것도 안 적혀있어야 됨)

2. 바로 push를 한다. 좌상단에 origin :  mybranch (New) 라고 돼있으면 OK. 

3. origin : mybranch 따블클릭하면 이름 바꿀 수 있다. 실제 Github repository에 님의 브랜치를 생성하는 과정

![test1](E:\Documents\SQL\mybranch.jpg)

그 후 이 브랜치에만 Push 하면 됨. 

#### 주의점

Pull을 사용하지 말 것, 차라리 Merge  into current를 쓰자. Merge into current에서 문제가 나면 zoom 화면공유할때 물어보셈

내 작업물이 master에 합쳐지길 원한다면 github 내에서 pull request를 보내던가 아님 나한테 카톡하셈 

