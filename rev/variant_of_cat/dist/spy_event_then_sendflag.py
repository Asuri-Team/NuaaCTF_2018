from web3 import Web3,HTTPProvider
import os
import time
import binascii
import base64
import smtplib
from email.mime.text import MIMEText
from email.header import Header
contract_address = "0x774158Fc75410cF425De5C0AeeEB360a41a98A6e"
contract_topic0 = "0x849abe7f874093e9f29cfa96fa016fa013e2d2a8d9aee6c76fa279b72b3a2187"
rpc = "https://rinkeby.infura.io/v3/c8a0e9764dc94846958d36c766dd87b5"


flag = "flag{https://cryptozombies.io}"
email = {
    "host":"smtp.qq.com",
    "port":587,
    "user":"doublemice@qq.com",
    # authorization code 
    "code":"ovsospdkzbagbcbh"
}
# initial
w3 = Web3(Web3.HTTPProvider(rpc))
sender = smtplib.SMTP(host=email["host"],port=email["port"])
sender.ehlo()
sender.starttls()
sender.login(email["user"],email["code"])

# email content
message = MIMEText("表哥，收下你的flag:"+flag, 'plain', 'utf-8')
message["From"] = Header("Asuri:variant_of_cat","utf-8")
message["Subject"] = Header("variant_of_cat flag","utf-8")


def sendflag(toEmail):
    message["To"] = Header(toEmail,"utf-8")
    sender.sendmail(email["user"],toEmail,message.as_string())
    # log
    os.system("echo "+time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) +": Get flag -- "+toEmail+" >> /tmp/variant_of_cat.log")
    print("send success")


def event():
    flag_logs = w3.eth.getLogs({
            "address":contract_address,
            "topic0":contract_topic0
        })
    if flag_logs is not []:
        for flag_log in flag_logs:
            data = flag_log["data"][2:]
            length = int(data[64*2:64*3].replace('00', ''),16)
            data = data[64*3:][:length*2]
            b64email = binascii.unhexlify(data).decode('utf-8')
            try:
                email = base64.b64decode(b64email).decode('utf-8')
                sendflag(email)
            except:
                errmsg = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())+":decode or send to b64 - {} fail".format(b64email)
                os.system("echo " + errmsg + ">> /tmp/variant_of_cat_error.log")
                print(errmsg)
while(True):
    event()
    time.sleep(15)

