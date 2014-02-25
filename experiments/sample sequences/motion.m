orig=checkerboard>.5;

%Skew
tform=affine2d([1 0 0; .5 1 0; 0 0 1]);
[skew, r0, r1] = velfield(orig, tform);
%A = padarray(A,[200 200]);
figure(1)
quiver(r0(:,:,1),flipud(r0(:,:,2)),skew(:,:,1),skew(:,:,2))
axis('equal');

%Scale
tform=affine2d([2 0 0; 0 2 0; 0 0 1]);
[scale, r0, r1] = velfield(orig, tform);
%A = padarray(A,[200 200]);
figure(2)
quiver(r0(:,:,1),flipud(r0(:,:,2)),scale(:,:,1),scale(:,:,2))
axis('equal');

%Rotate
theta=1;
tform=affine2d([cosd(theta) -sind(theta) 0; sind(theta) cosd(theta) 0; 0 0 1]);
[rotate, r0, r1] = velfield(orig, tform);
%A = padarray(A,[200 200]);
figure(3)
quiver(r0(:,:,1),flipud(r0(:,:,2)),rotate(:,:,1),rotate(:,:,2))
axis('equal');

%Translate
tform=affine2d([1 0 0; 0 1 0; -5 5 1]);
[translate, r0, r1] = velfield(orig, tform);
%A = padarray(A,[200 200]);
figure(4)
quiver(r0(:,:,1),r0(:,:,2),translate(:,:,1),translate(:,:,2))
axis('equal');

%Fracture
%tform=affine2d([]);
%[fracture, r0, r1] = velfield(orig, tform);
%A = padarray(A,[200 200]);
%figure(5)
%quiver(r0(:,:,1),flipud(r0(:,:,2)),A(:,:,1),A(:,:,2))
%axis('equal');