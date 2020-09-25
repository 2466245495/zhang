
print("欢迎使用加解密码机1.3")
print('本机只支持数字，英文的加密')
while True:
    A=int(input('输入1为加密，输入2为解密，输入其他为结束'))
    if A==1:
        K=3
        A=input("请输入你想要加密的密码")
        K=int(input("请输入你先要的偏移量"))
        list1=list(A)
        list2=list1
        i=0    
        while  i<len(list1):
                if 97-K<=ord(list1[i])<123-K:
                    list2[i]=chr(ord(list1[i])+K)
                elif ord(list1[i])>=123-K:
                    list2[i]=chr(ord(list1[i])+K-26)
                elif 65-K<=ord(list1[i])<=90-K:
                    list2[i]=chr(ord(list2[i])+K)
                elif 90-K<=ord(list1[i]):
                    list2[i]=chr(ord(list1[i])+K-26)
                elif 48<=ord(list1[i])<=57-K:
                    list2[i]=chr(ord(list1[i])+K)
                elif ord(list1[i])>57-K:
                    list2[i]=chr(ord(list1[i])+K-10)
                else:
                    list2[i]=chr(ord(list1[i]))
                i=i+1
        print ("加密结果为："+"".join(list2))        
    elif A==2:
        K=3
        B=input("请输入你想要解密的密码")
        K=int(input("请输入你解密要的偏移量"))
        list3=list(B)
        list4=list3
        i=0
        while  i<len(list3):
            if 97+K<=ord(list3[i])<=122+K:
                list4[i]=chr(ord(list3[i])-K)
            elif 90<ord(list3[i])<97+K:
                list4[i]=chr(ord(list3[i])+26-K)
            elif 65+K<=ord(list3[i])<=90+K:
                list4[i]=chr(ord(list3[i])-K)
            elif 57<ord(list3[i])<65+K:
                list4[i]=chr(ord(list3[i])+26-K)
            elif 48+K<=ord(list3[i])<=57+K:
                list4[i]=chr(ord(list3[i])-K)
            elif 32<ord(list3[i])<48+K:
                list4[i]=chr(ord(list3[i])+10-K)
            else:
                list4[i]=chr(ord(list3[i]))
            i=i+1    
        print("解密结果为："+"".join(list4))
    else :
        print("结束")
        break
