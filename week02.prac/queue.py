class queue_htm:
    def __init__(self):
        self.queue=list ()
    def Enqueue(self,data):
        self.queue.append(data)
        return self.queue  ###데이터를 입력하여 추가하고 리스트를 반환한다. 
    def Dequeue(self): ####뽑아내는ㄴ거
        try:
            temp=self.queue[0] ### 첫번째를 뽑아냄 제일 먼저  
            del self.queue[0] ###0번째를 리스트에서 삭제한다. 
            return temp ## 0번째를 반환한다. 
        except:
            return self.queue ##예외가 발생했을때 처리하는 코드 
    def qsize(self):
        return len(self.queue)
    
HTM = queue_htm()
# Enqueue
HTM.Enqueue(1)
HTM.Enqueue(2)
HTM.Enqueue(3)
HTM.Enqueue(4)
HTM.Enqueue(5)


# qsize
print('==>> qsize : ',HTM.qsize())
# Dequeue
for _ in range(HTM.qsize()):
    print('==>> Dequeue : ',HTM.Dequeue())
    print('==>> qsize : ',HTM.qsize())