N = input('please input N\n')
A=input('please input Matrix\n')

for k=1 : N-1
    if(k==N) 
        break
    end
    Max=-1
    Maxp=-1
    for i=k : N
        if(abs(A(i,k))>Max)
            Max=abs(A(i,k))
            Maxp=i
        end
    end
    
    if(Maxp~=k)
        TT=A(k,:)
        A(k,:)=A(Maxp,:)
        A(Maxp,:)=TT
    end
    for i=k+1 : N
        A(i,k)=A(i,k)/A(k,k)
    end
    for i=k+1 : N
        for j=k+1 : N
            A(i,j)=A(i,j)-A(i,k)*A(k,j)
        end
    end

end

        
          