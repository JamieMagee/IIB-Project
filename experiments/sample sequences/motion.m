ceilfix = @(x)ceil(abs(x)).*sign(x);
orig=checkerboard>.5;

%Skew
s = 0.5;
A = cat(3, 255*ones(size(orig, 1))*.5, 255*ones(size(orig, 1))*.5);
%A = cat(3, 255*ones(10)*.5, 255*ones(10)*.5);
for i = 1:size(A, 1)
   A(i,:,2) = -ceilfix((size(A, 1)+1)/2 - i)*s;
end
A = padarray(A,[200 200],0.5*255);
figure(1)
subplot(1,2,1)
imshow(A(:,:,1), [0 255]);
title('Y-direction')
subplot(1,2,2)
imshow(A(:,:,2), [0 255]);
title('X-direction')

%Scale
A = cat(3, 255*ones(size(orig, 1))*.5, 255*ones(size(orig, 1))*.5);
%A = cat(3, 255*ones(10)*.5, 255*ones(10)*.5);
for i = 1:size(A, 2)
   A(:,:,2) = ceilfix(sqrt(spiral(size(A,1)))/2);
   A(:,:,1) = ceilfix(sqrt(spiral(size(A,1)))/2);
end
A = padarray(A,[200 200],0.5*255);
figure(2)
subplot(1,2,1)
imshow(A(:,:,1), [0 255]);
title('Y-direction')
subplot(1,2,2)
imshow(A(:,:,2), [0 255]);
title('X-direction')

%Rotate
A = cat(3, 255*ones(size(orig, 1))*.5, 255*ones(size(orig, 1))*.5);
%A = cat(3, 255*ones(10)*.5, 255*ones(10)*.5);
theta = 1;
for i = 1:size(A,2)
    A(i,:,2) = ceilfix((size(A, 2)+1)/2 - i);
    A(:,i,1) = -ceilfix((size(A, 2)+1)/2 - i);
end
A = padarray(A,[200 200],0.5*255);
figure(3)
subplot(1,2,1)
imshow(A(:,:,1), [0 255]);
title('Y-direction')
subplot(1,2,2)
imshow(A(:,:,2), [0 255]);
title('X-direction')

%Translate
A = cat(3, 255*ones(size(orig, 1))*.5, 255*ones(size(orig, 1))*.5);
%A = cat(3, 255*ones(10)*.5, 255*ones(10)*.5);
theta = 1;
for i = 1:size(A,2)
    A(i,:,2) = 5;
    A(:,i,1) = 5;
end
A = padarray(A,[200 200],0.5*255);
figure(4)
subplot(1,2,1)
imshow(A(:,:,1), [0 255]);
title('Y-direction')
subplot(1,2,2)
imshow(A(:,:,2), [0 255]);
title('X-direction')

%Fracture
A = cat(3, 255*ones(size(orig, 1))*.5, 255*ones(size(orig, 1))*.5);
%A = cat(3, 255*ones(10)*.5, 255*ones(10)*.5);
theta = 1;
for i = 1:size(A,2)
    A(:,i,1) = -sign(ceilfix((size(A, 2)+1)/2 - i))*5;
end
A = padarray(A,[200 200],0.5*255);
figure(5)
subplot(1,2,1)
imshow(A(:,:,1), [0 255]);
title('Y-direction')
subplot(1,2,2)
imshow(A(:,:,2), [0 255]);
title('X-direction')