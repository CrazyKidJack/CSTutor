#!/usr/bin/python3
import requests
import sys

gitHubLoginURL = "https://github.com/session"
gitHubLoginPayload = "authenticity_token=Vp6LJGxaSYuIxfgjLbBlIfBmbugfW9MVW2Dt97vFIU5nnZLTgIGVAepAq9AdUfvctFphm41M61FrAOdeZOo5Mg%3D%3D&login=jackpfeffer%40yahoo.com&password=h%22%3CJ4JJu3yk1%3D5cG.ij2cxdP%60P%3A%7Dd%7B5rML_p%29w%23vN%27%28n43%5C%7D%7B%25kE%25tf%23&return_to=%2Flogin%2Foauth%2Fauthorize%3Fclient_id%3D7bb0a7ec13388aa67963%26duration%3Dtemporary%26redirect_uri%3Dhttps%253A%252F%252Fadventofcode.com%252Fauth%252Fgithub%252Fcallback%26response_type%3Dcode%26scope%3D%26state%3Dx"
gitHubLoginCookie = {"_gh_sess":"2zBuKnYTUVa9UIuEWGpa6XZu9PZlzd42bKbOikZIShleCxuGUMC%2Bhcxg2voyr9qiZ8BgehfnDYado9knueBNdNPiE9%2FYgcCrIYRdOyDB6cgJoDZ4YyXjkvB083ryn1Krtp7de%2F3jKUptV8DsQawECzB9yiLauwuCvHZFbNP8I9AxUPImEef2FJBC8xD%2BPCr2DbSDMmwSACUwE59G1umgg9DzU%2BDTQDNe0rrTjI4BRHaV1kh1RkIRbx3rhvTIfq2Ku11YZm%2FlfY2W8OLnfrNCjw%3D%3D--tE%2Brj%2FzNBpyydFRQ--OXKDiqnXsfNOnb0jbAQtcw%3D%3D"}
#gitHubLoginCookie = {"_gh_sess":"B5Bdy6E99G3BybAUNrZbgUWX0wQVQPTQFA6Dhu3JUeck6Y3AUnC7%2BOj6u0ZRYv68gWfenooiW2UrNwJASIvr345KvnCKNWZ6RgNjzkwddIHl5uohzQin3BdQASundvHA7oS81lnhjhCNJHnyETtl3yhYcwUhnzrJW6blDn9mC2xMwDbUDYbRuXQFTGflbIUHN%2FoaLygCofuWhLJSYd%2Bms%2BJvNYb8D64Yb1C0WB57%2F1KhEzOjTsgvaXEilyht2GdmxoLqrWzp7xdpmpM9L5y0IA%3D%3D--w9%2BJEC10cIsJw48b--EkXKalLFYkB35TmYkPBQYQ%3D%3D"}
gitHubLoginSession = requests.Session()
# all cookies received will be stored in the session object

#gitHubLoginResponse = gitHubLoginSession.post(gitHubLoginURL, gitHubLoginPayload, allow_redirects=False, cookies=gitHubLoginCookie)
gitHubLoginResponse = gitHubLoginSession.post(gitHubLoginURL, gitHubLoginPayload, cookies=gitHubLoginCookie)
#print(gitHubLoginResponse.text)
#print(gitHubLoginResponse.url)

reportUrl = "https://adventofcode.com/2020/day/1/input"
reportResponse = gitHubLoginSession.get(reportUrl)
print(reportResponse.text)
