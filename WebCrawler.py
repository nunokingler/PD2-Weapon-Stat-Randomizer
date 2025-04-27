from weapon_links import get_weapon_links
from bs4 import BeautifulSoup
import requests
import time
import re
import csv

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"
}

# Quick map of headings to example WeaponType and WeaponClass values
# You’ll want to replace these with your actual enum mapping later
def infer_type_and_class(heading):
    return heading
    heading = heading.lower()
        
def parse_names_from_stat_table(soup, fallback_name):
    internalName = ""
    inGameName = ""

    tables = soup.find_all("table")
    for table in tables:
        rows = table.find_all("tr")
        for row in rows:
            cells = row.find_all("td")
            if len(cells) != 2:
                continue

            label = cells[0].get_text(strip=True).lower()
            raw_value = cells[1]

            if "internal name" in label and not internalName:
                # Break the content into parts (handles multiple lines inside <td>)
                parts = [t.strip() for t in raw_value.stripped_strings]
                filtered = [p for p in parts if "npc" not in p.lower()]
                if filtered:
                    internalName = filtered[0]
                elif parts:
                    internalName = parts[0]
                else:
                    internalName = f"FALLBACK_INTERNAL_{fallback_name.upper()}"

            elif "in-game name" in label and not inGameName:
                inGameName = cells[1].get_text(strip=True)

    # Fallbacks if still empty
    if not internalName:
        internalName = f"FALLBACK_INTERNAL_{fallback_name.upper()}"
    if not inGameName:
        h1 = soup.find("h1")
        inGameName = h1.get_text(strip=True) if h1 else f"FALLBACK_INGAME_{fallback_name.upper()}"

    return internalName, inGameName
    return internalName, inGameName
def parse_stat_block(soup):
    stats = {
        "damage": 0, "concealment": 0, "rateOfFire": 0, "accuracy": 0,
        "stability": 0, "ammoLow": 0.0, "ammoHigh": 0.0,
        "magSize": 0, "ammoTotal": 0,
        "reloadTactical": 0.0
    }

    tables = soup.find_all("table")

    for table in tables:
        rows = table.find_all("tr")
        for row in rows:
            cells = row.find_all("td")
            if len(cells) != 2:
                continue

            label = cells[0].get_text(strip=True).lower()
            value = cells[1].get_text(strip=True).replace(",", "")

            try:
                if label == "damage" and stats["damage"] == 0:
                    stats["damage"] = int(re.search(r'\d+', value).group())
                elif label == "concealment" and stats["concealment"] == 0:
                    stats["concealment"] = int(re.search(r'\d+', value).group())
                elif label == "rate of fire" and stats["rateOfFire"] == 0:
                    stats["rateOfFire"] = int(re.search(r'\d+', value).group())
                elif label == "accuracy" and stats["accuracy"] == 0:
                    stats["accuracy"] = int(re.search(r'\d+', value).group())
                elif label == "stability"and stats["stability"] == 0:
                    stats["stability"] = int(re.search(r'\d+', value).group())
                elif label == "magazine"and stats["magSize"] == 0:
                    stats["magSize"] = int(re.search(r'\d+', value).group())
                elif label == "total ammo"and stats["ammoTotal"] == 0:
                    stats["ammoTotal"] = int(re.search(r'\d+', value).group())
            except:
                continue

        # Ammo pickup and reload speeds are in special nested stats tables
        table_text = table.get_text().lower()

        if "base pickup" in table_text and stats["ammoLow"]==0 and stats["ammoHigh"]==0:
            pickups = re.findall(r'base pickup\s*(\d+\.?\d*)\s*(\d+\.?\d*)', table_text)
            if pickups:
                stats["ammoLow"] = float(pickups[0][0])
                stats["ammoHigh"] = float(pickups[0][1])

        if "base time" in table_text and stats["reloadTactical"]==0:
            # Match the line that says 'Base time' and grab the next float value
            base_time_match = re.search(r'base time\s*(\d+\.?\d*)s', table_text)
            if base_time_match:
                stats["reloadTactical"] = float(base_time_match.group(1))

    return stats

# Start
print("internalName,type,category,inGameName,damage,concealment,rateOfFire,accuracy,stability,ammoLow,ammoHigh,magSize,ammoTotal")

with open("scraped_weapon_data.csv", mode="w", newline="", encoding="utf-8") as csvfile:
    writer = csv.writer(csvfile)

all_weapons = []

for heading, weapons in get_weapon_links():
    wType = heading

    for name, url in weapons:
        try:
            response = requests.get(url, headers=headers)
            soup = BeautifulSoup(response.text, "html.parser")
            stats = parse_stat_block(soup)

            internalName, inGameName = parse_names_from_stat_table(soup, name)

            # Print in CSV format
            print(f"{internalName},{inGameName}, {wType},"
                  f"{stats.get('damage', 0)},"
                  f"{stats.get('rateOfFire', 0)},"
                  f"{stats.get('concealment', 0)},"
                  f"{stats.get('accuracy', 0)},"
                  f"{stats.get('stability', 0)},"
                  f"{stats.get('reloadTactical', 0.0)},"
                  f"{stats.get('ammoTotal', 0)},"
                  f"{stats.get('magSize', 0)},"
                  f"{stats.get('ammoLow', 0.0)},"
                  f"{stats.get('ammoHigh', 0.0)}")
                  
            weapon_data = {
                "internalName": internalName,
                "type": wType,
                "inGameName": inGameName,
                "damage": stats.get("damage", 0),
                "concealment": stats.get("concealment", 0),
                "rateOfFire": stats.get("rateOfFire", 0),
                "accuracy": stats.get("accuracy", 0),
                "stability": stats.get("stability", 0),
                "ammoLow": stats.get("ammoLow", 0.0),
                "ammoHigh": stats.get("ammoHigh", 0.0),
                "magSize": stats.get("magSize", 0),
                "ammoTotal": stats.get("ammoTotal", 0),
                "reloadTactical": stats.get("reloadTactical", 0.0)
            }
            # Store to final list
            all_weapons.append(weapon_data)

            time.sleep(0.05)  # Be nice to the server
        except Exception as e:
            print(f"# Failed to parse {name} ({url}): {e}")
            
with open("scraped_weapon_data.csv", mode="w", newline="", encoding="utf-8") as csvfile:
    writer = csv.writer(csvfile)

    # Write data rows
    for weapon in all_weapons:
        writer.writerow([
            weapon["internalName"], weapon["inGameName"], weapon["type"],
            weapon["damage"], weapon["rateOfFire"],weapon["concealment"],
            weapon["accuracy"], weapon["stability"],
            weapon["reloadTactical"], weapon["magSize"], weapon["ammoTotal"], 
            weapon["ammoLow"], weapon["ammoHigh"],
        ])
    '''        
    for weapon in all_weapons:
        writer.writerow([
            weapon["internalName"],weapon["type"],weapon["type"], weapon["inGameName"], 
            weapon["damage"],weapon["concealment"], weapon["rateOfFire"],
            weapon["accuracy"], weapon["stability"],
            weapon["ammoLow"], weapon["ammoHigh"], weapon["magSize"],
             weapon["ammoTotal"]
        ])
        ''' 