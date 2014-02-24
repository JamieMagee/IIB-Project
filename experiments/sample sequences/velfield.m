function [V, r0, r1] = velfield(X, tform)
%VELFIELD Function that takes an image X and a transform object tform and 
% returns a velocity field V, where each entry is the direction that each 
% pixel of X is moved in when X undergoes the transform tform.
%
%   X is an n x m image array
%   tform is a transform object (affine2d or projective2d)
%
%   V is an n x m x 2 array, where V(n,m,1) is the x component that the
%       [n,m] pixel in X is moved by tform and V(n,m,2) is the y component
%       of that movement

% Define size of X.
[n,m] = size(X);

% Set up matrix of points r0.
r0 = ones(n*m, 3);
for i = 1:n
    r0(i:m:(n*m),2) = i;
end
for j = 1:m
    r0((n*(j-1) + 1):n*j,1) = j;
end

% Calculate new positions for all points r0 after transformation under
%   tform, which are r1.
r1 = r0*tform.T;
r1(:,1) = r1(:,1)./r1(:,3);
r1(:,2) = r1(:,2)./r1(:,3);

% Eliminate third column (now unneeded)
r0_ = r0(:,1:2);
r1_ = r1(:,1:2);

% Calculate stacked matrix of velocities, v.
v = r1_ - r0_;

% Reshape v into V
V = reshape(v, [n m 2]);
r0 = reshape(r0_, [n m 2]);
r1 = reshape(r1_, [n m 2]);

% Plotting code
% str = [];
% for i = 16:16:n
%     for j = 16:16:m
%         str = ([str, '[',int2str(j),',',int2str(j),' + V(',int2str(i),',',int2str(j),',1)],'...
%             '[',int2str(i),',',int2str(i),' + V(',int2str(i),',',int2str(j),',2)], ']);
%     end
% end
% figure; eval(['plot(',str,' ''k'');']);
quiver(r0(:,:,1),flipud(r0(:,:,2)),V(:,:,1),V(:,:,2))
axis('equal');
end

