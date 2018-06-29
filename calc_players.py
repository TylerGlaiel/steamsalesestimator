#Code by Tyler Glaiel
#usage: "calc_players [steam app id]"
#Compile "estimate_sales.cpp" to "estimate_sales.exe" first with a c++ compiler like gcc or something.

import urllib.request, json
import subprocess
import argparse

parser = argparse.ArgumentParser(description='Calculate players for a steam game')
parser.add_argument('gameid', type=str, action='store',
                    help='steam game id')


args = parser.parse_args()

gameid = str(args.gameid)

def GetAchievementData(gameid):
    addr = "http://api.steampowered.com/ISteamUserStats/GetGlobalAchievementPercentagesForApp/v0002/?"+gameid;
    with urllib.request.urlopen(addr) as url:
        data = json.loads(url.read().decode())

    percents = []
    for x in data["achievementpercentages"]["achievements"]:
        pcent = x["percent"]
        ptext = str(x["percent"])
        if pcent > 0 and pcent < 100:
            percents.append(ptext)
        
    return percents
    

percents = GetAchievementData(gameid)

sales = subprocess.check_output(['estimate_sales', *percents])
print(sales.decode('utf-8'))
