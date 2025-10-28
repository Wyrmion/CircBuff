1) For use it plz clone https://github.com/Wyrmion/wheap

2) Call constructor 

~~~c
CircBuff_t*  CircBuffTx = NULL;

if((CircBuffTx = CircBuff_ctor(IntBuffSize,CircDeep)) == NULL)
    while(1); /*Bug catch*/
~~~

3) Push data to buffer 

~~~c
CircBuff_push(CircBuffTx,pack,pack_leng);
~~~

4) Pop data from buffer 

~~~c
if(CircBuff_IsFree(cthis->CircBuffRx))
    return;
else 
    CircBuff_pop(cthis->CircBuffRx,dst,&leng);

~~~
