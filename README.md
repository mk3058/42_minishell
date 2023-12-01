# 42Seoul Minishell

## ✏️ Project Description

간소화된 Unix Shell을 구현하는 프로젝트입니다.   
MacOS 환경에서 Bash를 참고하며 프로젝트를 진행하였습니다.

1. 개발 기간 : 2023.01.16 ~ 2023.02.09   

## 💻 Features
```
1. 명령어 실행: 사용자가 입력한 UNIX 명령어(ls, echo 등)와 옵션(ls의 -a 등)을 처리합니다.
2. 파이프라인 및 리다이렉션: 여러 명령어 간의 파이프(|)와 파일 입출력 리다이렉션(>, <, <<, >>)을 지원합니다.
3. 환경 변수 관리: export, unset, env 등의 명령어를 통해 환경 변수를 추가, 제거, 조회할 수 있습니다.
4. 시그널 처리: Ctrl-C, Ctrl-D, Ctrl-\와 같은 시그널을 처리할 수 있습니다.
```

## ⚙️ Stacks
### Development
<img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=C&logoColor=white"> <img src="https://img.shields.io/badge/cmake-064F8C?style=for-the-badge&logo=cmake&logoColor=white">

### Environment
<img src="https://img.shields.io/badge/github-181717?style=for-the-badge&logo=github&logoColor=white"> <img src="https://img.shields.io/badge/git-F05032?style=for-the-badge&logo=git&logoColor=white"> <img src="https://img.shields.io/badge/visual%20studio%20code-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white">   
<img src="https://img.shields.io/badge/macOS-000000?style=for-the-badge&logo=macOS&logoColor=white">
<img src="https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white">



### Contributor
   - bojung (@bojung)
   - minkyuki (@mk3058)
   
### Used Library

- [GNU - readline](https://tiswww.cwru.edu/php/chet/readline/rltop.html)     

## 💻 How to Run

```
1. clone this repo
	- git clone https://github.com/mk3058/42_minishell.git

2. install dependencies (GNU - readline)

3. build project
	- make

4. Launch
	- ./minishell
```
