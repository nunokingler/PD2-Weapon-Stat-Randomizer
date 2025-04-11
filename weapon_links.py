from bs4 import BeautifulSoup
import requests

def get_weapon_links():

    #weapons = [("testing", "https://payday.fandom.com/wiki/Golden_AK.762")]
    #grouped = [("testing", weapons)]
    #return grouped
    
    url = "https://payday.fandom.com/wiki/Weapons_(Payday_2)/List_of_Weapons"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"
    }

    response = requests.get(url, headers=headers)
    soup = BeautifulSoup(response.text, "html.parser")

    SKIP_KEYWORDS = ["melee", "throwable", "grenade", "launcher", "saw"]
    tables = soup.find_all("table", class_=lambda c: c and "wikitable" in c and "sortable" in c)

    grouped = []  # List of (heading, [(name, url), ...])

    for table in tables:
        heading = table.find_previous(["h2", "h3"])
        heading_text = heading.get_text(strip=True) if heading else "Unknown"

        if any(keyword in heading_text.lower() for keyword in SKIP_KEYWORDS):
            continue

        weapons = []
        rows = table.find_all("tr")[1:]
        for row in rows:
            cells = row.find_all("td")
            if not cells:
                continue
            link_tag = cells[0].find("a", href=True)
            if not link_tag:
                continue
            name = link_tag.get_text(strip=True)
            full_url = "https://payday.fandom.com" + link_tag["href"]
            weapons.append((name, full_url))

        if weapons:
            grouped.append((heading_text, weapons))

    return grouped

# Print nicely if run standalone
if __name__ == "__main__":
    for heading, weapons in get_weapon_links():
        print(f"\n  |{heading}|")
        for name, url in weapons:
            print(f"{name}: {url}")