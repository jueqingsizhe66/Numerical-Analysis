    A=[ 1 3 1; 2 8 9; 3 7 1]
    b=[4;8;12]
    n = 3 
    L= zeros(n)
    U= zeros(n)
    U=A
    for k =1  : n-1
        for i = k+1 : n
            L(i,k)=U(i,k)./U(k,k)
        end
        for i= k+1 : n
            for j=k : n
                U(i,j)=U(i,j)-L(i,k)*U(k,j)           
            end
        end
        for i = k+1 : n
            b(i)=b(i)-L(i,k)*b(k)
        end
        L(k,k)=1
    end
    L(n,n)=1
    