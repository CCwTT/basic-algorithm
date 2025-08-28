import requests

resp=requests.get('http://www.google.com')
print(resp.status_code)