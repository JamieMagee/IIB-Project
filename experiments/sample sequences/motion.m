ceilfix = @(x)ceil(abs(x)).*sign(x);
orig=checkerboard>.5;

%Skew
s = 0.5;
A = cat(3, zeros(size(padarray(orig,[256 256]),1)), zeros(size(padarray(orig,[256 256]),1)));
A = cat(3, zeros(10), zeros(10));
for i = 1:size(A, 2)
   A(i,:,2) = -ceilfix((size(A, 2)+1)/2 - i)*s;
end

%Scale
A = cat(3, zeros(size(padarray(orig,[256 256]),1)), zeros(size(padarray(orig,[256 256]),1)));
A = cat(3, zeros(10), zeros(10));
for i = 1:size(A, 2)
   A(:,:,2) = ceilfix(sqrt(spiral(size(A,1)))/2);
   A(:,:,1) = ceilfix(sqrt(spiral(size(A,1)))/2);
end

%Rotate
A = cat(3, zeros(size(padarray(orig,[256 256]),1)), zeros(size(padarray(orig,[256 256]),1)));
A = cat(3, zeros(10), zeros(10));
theta = 1;
for i = 1:size(A,2)
    A(i,:,2) = ceilfix((size(A, 2)+1)/2 - i);
    A(:,i,1) = -ceilfix((size(A, 2)+1)/2 - i);
end

%Translate
A = cat(3, zeros(size(padarray(orig,[256 256]),1)), zeros(size(padarray(orig,[256 256]),1)));
A = cat(3, zeros(10), zeros(10));
theta = 1;
for i = 1:size(A,2)
    A(i,:,2) = 5;
    A(:,i,1) = 5;
end

%Disjoint
A = cat(3, zeros(size(padarray(orig,[256 256]),1)), zeros(size(padarray(orig,[256 256]),1)));
A = cat(3, zeros(10), zeros(10));
theta = 1;
for i = 1:size(A,2)
    A(:,i,1) = -sign(ceilfix((size(A, 2)+1)/2 - i))*5;
end

load('skew.lucas-kanade.avi.yml')

