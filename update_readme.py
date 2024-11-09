import requests

# GitHub API URL 설정
OWNER = "shinhong-gyu"         # 리포지토리 소유자
REPO = "Brotato_ToyProject"           # 리포지토리 이름
API_URL = f"https://api.github.com/repos/{OWNER}/{REPO}/contributors"

# GitHub API로부터 기여자 정보 가져오기
def get_contributors():
    response = requests.get(API_URL)
    if response.status_code == 200:
        return response.json()
    else:
        print(f"Error fetching contributors: {response.status_code}")
        return []

# README 파일 업데이트하기
def update_readme(contributors):
    # README 파일 열기
    with open("README.md", "r") as file:
        readme_content = file.readlines()

    # 기여자 섹션 업데이트
    start_marker = "<!-- CONTRIBUTORS_START -->\n"
    end_marker = "<!-- CONTRIBUTORS_END -->\n"
    new_content = start_marker

    # 기여자 정보 추가
    for contributor in contributors:
        new_content += f"- [{contributor['login']}]({contributor['html_url']}): {contributor['contributions']} commits\n"

    new_content += end_marker

    # 기존 README 내용에 반영하기
    with open("README.md", "w") as file:
        in_contributor_section = False
        for line in readme_content:
            if line == start_marker:
                in_contributor_section = True
                file.write(new_content)  # 새로운 기여자 섹션 추가
            elif line == end_marker:
                in_contributor_section = False
            elif not in_contributor_section:
                file.write(line)

if __name__ == "__main__":
    contributors = get_contributors()
    update_readme(contributors)
