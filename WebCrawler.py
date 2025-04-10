import requests
from bs4 import BeautifulSoup

BASE_URL = "https://payday.fandom.com"
LIST_PAGE = f"{BASE_URL}/wiki/Weapons_(Payday_2)/List_of_Weapons#Primary"

def get_weapon_links():
    response = requests.get(LIST_PAGE)
    soup = BeautifulSoup(response.text, "html.parser")

    weapon_links = {}

    # Main content section
    content = soup.find("div", class_="mw-parser-output")
    if not content:
        print("Could not find main content area.")
        return weapon_links

    # Find all <a> tags with hrefs that link to weapon pages
    for a in content.find_all("a", href=True):
        href = a['href']
        name = a.get_text(strip=True)
        if href.startswith("/wiki/") and ":" not in href and name:
            full_url = BASE_URL + href
            weapon_links[name] = full_url

    return weapon_links

def main():
    weapon_links = get_weapon_links()
    for name, url in weapon_links.items():
        print(f"{name}: {url}")

if __name__ == "__main__":
    main()