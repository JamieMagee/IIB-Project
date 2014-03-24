clear all
close all
clc

orig = checkerboard > .5;
files = dir('*.txt');
diary('16.txt');
subsampling = 16

for file = files'
    if strfind(file.name, 'timings') == 1
        continue;
    end
    flow = load(file.name);
    flow = reshape(flow,sqrt(size(flow,1)),sqrt(size(flow,1)),2);
    flow(:,:,1)=flow(:,:,1)';
    flow(:,:,2)=flow(:,:,2)';
    actual = zeros(size(flow));
    if strfind(file.name, 'translate') == 1
        tform=affine2d([1 0 0; 0 1 0; -5 5 1]);
        actual = velfield(orig, tform);
        actual = padarray(actual,[200 200],0);
    elseif strfind(file.name, 'rotate') == 1
        theta=1;
        tform=affine2d([cosd(theta) -sind(theta) 0; sind(theta) cosd(theta) 0; 0 0 1]);
        actual = velfield(orig, tform);
        actual = padarray(actual,[200 200],0);
    elseif strfind(file.name, 'scale') == 1
        tform=affine2d([2 0 0; 0 2 0; 0 0 1]);
        actual = velfield(orig, tform);
        actual = padarray(actual,[200 200],0);
    elseif strfind(file.name, 'skew') == 1
        tform=affine2d([1 0 0; .5 1 0; 0 0 1]);
        actual = velfield(orig, tform);
        actual = padarray(actual,[200 200],0);
        actual(:,:,1) = actual(:,:,2);
    elseif strfind(file.name, 'fracture') == 1
        continue;
        %tform=affine2d([]);
        %actual = velfield(orig, tform);
        %actual = padarray(actual,[200 200],0);
    end
    actual = actual(1:subsampling:end,1:subsampling:end,:);
    sse = abs(sum(sum(sum(actual-flow),2),3));
    disp(file.name)
    disp(sse)
end
diary off;