# [프로그래머스] Lv 2. 튜플

문제 링크: [](https://programmers.co.kr/learn/courses/30/lessons/64065)

##### 문제 설명

셀수있는 수량의 순서있는 열거 또는 어떤 순서를 따르는 요소들의 모음을 튜플(tuple)이라고 합니다. n개의 요소를 가진 튜플을 n-튜플(n-tuple)이라고 하며, 다음과 같이 표현할 수 있습니다.

- (a1, a2, a3, ..., an)

튜플은 다음과 같은 성질을 가지고 있습니다.

1. 중복된 원소가 있을 수 있습니다. ex : (2, 3, 1, 2)
2. 원소에 정해진 순서가 있으며, 원소의 순서가 다르면 서로 다른 튜플입니다. ex : (1, 2, 3) ≠ (1, 3, 2)
3. 튜플의 원소 개수는 유한합니다.

원소의 개수가 n개이고, **중복되는 원소가 없는** 튜플 `(a1, a2, a3, ..., an)`이 주어질 때(단, a1, a2, ..., an은 자연수), 이는 다음과 같이 집합 기호 '{', '}'를 이용해 표현할 수 있습니다.

- {{a1}, {a1, a2}, {a1, a2, a3}, {a1, a2, a3, a4}, ... {a1, a2, a3, a4, ..., an}}

예를 들어 튜플이 (2, 1, 3, 4)인 경우 이는

- {{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}}

와 같이 표현할 수 있습니다. 이때, 집합은 원소의 순서가 바뀌어도 상관없으므로

- {{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}}
- {{2, 1, 3, 4}, {2}, {2, 1, 3}, {2, 1}}
- {{1, 2, 3}, {2, 1}, {1, 2, 4, 3}, {2}}

는 모두 같은 튜플 (2, 1, 3, 4)를 나타냅니다.

특정 튜플을 표현하는 집합이 담긴 문자열 s가 매개변수로 주어질 때, s가 표현하는 튜플을 배열에 담아 return 하도록 solution 함수를 완성해주세요.

#### **[제한사항]**

- s의 길이는 5 이상 1,000,000 이하입니다.
- s는 숫자와 '{', '}', ',' 로만 이루어져 있습니다.
- 숫자가 0으로 시작하는 경우는 없습니다.
- s는 항상 중복되는 원소가 없는 튜플을 올바르게 표현하고 있습니다.
- s가 표현하는 튜플의 원소는 1 이상 100,000 이하인 자연수입니다.
- return 하는 배열의 길이가 1 이상 500 이하인 경우만 입력으로 주어집니다.



### 풀이

문제가 길고 설명이 복잡하지만, 결국 문제에서 해야 되는 일을 정리하면 다음과 같다.

1. 입력 <b>문자열</b> 토큰화 (Input 가공)
2. 집합 데이터가 가지는 <b>법칙</b>에 따라 튜플 생성
3. 튜플 출력 (Output 가공)

2번의 법칙 또한 간단하다. n-튜플에서 i번째 요소는 n+1-i번만큼 집합에 등장하므로, 집합에서 각 원소의 등장 횟수를 일괄적으로 센 후 정렬해서 출력하면 끝이다. 처음 풀 때는 복잡해 보였는데 레벨이 2인 이유가 있는 모양.



프로그램의 로직을 정리하면 다음과 같다.

1. 입력 문자열에서 숫자만 추출한 후 input_list에 저장

2. map 자료구조에 input_list에 있는 아이템을 Key 값으로 insert 한다. Value는 1씩 증가.

3. Value 값으로 정렬해야 하므로 vector로 변환한 후 Sort

4. 위 정렬된 리스트의 Key값을 순서대로 출력

   

입력 문자열 가공을 위해 C++에서 제공하는 regex를 사용했다. 숫자의 총 등장횟수만 뽑을 것이므로 정규 표현식이 간단하다.  

```c++
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
using namespace std;

vector<int> solution(string s) {
	vector<int> answer = {};
    vector<int> input_list = {};
	map<int, int> mapped_item;
    
    //데이터 추출
	regex re("[0-9]+");
	sregex_iterator end;
    for(sregex_iterator it(s.begin(), s.end(), re);it!=end;++it)	
		input_list.push_back(stoi((*it).str()));
    
    //등장횟수 카운트
	for (auto i : input_list)
		mapped_item[i]++;
    
	//map->vector 변환
	vector<pair<int, int>> sorted_item(mapped_item.begin(), mapped_item.end());
    
    //정렬
    auto comparison = [](pair<int, int> a, pair<int, int> b) {return a.second>b.second;};
	sort(sorted_item.begin(), sorted_item.end(), comparison);

    //출력
	for (auto i: sorted_item)
		answer.push_back(i.first);
    
    return answer;
}
```



