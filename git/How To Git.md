# How To Git

1. 폴더에서 오른쪽 클릭 -> git bash

2. git 초기화

   ```bash
   git init # 해당 폴더의 git 설정 초기화
   ```

3. git 관리 과정은 3가지 단계로 이루어진다.
   + 스테이징
   + 커밋
   + 푸시

### 스테이징

```bash
git add <file> # file을 스테이징(커밋할 준비)
git add .	   # 해당 디렉토리의 모든 폴더 + 파일을 스테이징
```





### 커밋

```bash
git status #커밋하기 전에 변경사항(파일추가, 삭제, 수정 등) 표시
git diff   #자세한 변경사항 표시(코드 단위로 비교 가능)
git commit -m "commit message" #해당 브랜치에 스테이징된 파일을 커밋한다.
```



### 설정

```bash
git config --global user.email "email@domain.com" #--global:전역 설정
git config --local		#--local: 지역 설정
```



### 저장소 지정 및 푸시

```bash
git remote add <repo_name> <url>   #repo_name 이름으로 url 원격 저장소를 지정
#example: origin 이라는 이름으로 github repository 지정. 미리 만들어놔야함
git remote add origin https://github.com/ResinCRT/git-test.git
git remote set-url <repo_name> <url> #repo_name에 있는 원격 저장소 주소 변경
git push <repo_name> <branch> #지정된 repository에 branch를 푸시
```
