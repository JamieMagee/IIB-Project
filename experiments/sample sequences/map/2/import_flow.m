clear all
close all
clc

delete('2.txt')
files = dir('*.txt');
diary('2.txt');
subsampling = 2

for file = files'
    orig = padarray(checkerboard > .5,[200 200],255);
    orig = orig(1:subsampling:end,1:subsampling:end);
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
    elseif strfind(file.name, 'rotate') == 1
        theta=1;
        tform=affine2d([cosd(theta) -sind(theta) 0; sind(theta) cosd(theta) 0; 0 0 1]);
        actual = velfield(orig, tform);
    elseif strfind(file.name, 'scale') == 1
        tform=affine2d([2 0 0; 0 2 0; 0 0 1]);
        actual = velfield(orig, tform);
    elseif strfind(file.name, 'skew') == 1
        tform=affine2d([1 0 0; .5 1 0; 0 0 1]);
        actual = velfield(orig, tform);
        actual(:,:,1) = actual(:,:,2);
    elseif strfind(file.name, 'fracture') == 1
        continue;
        %tform=affine2d([]);
        %actual = velfield(orig, tform);
        %actual = padarray(actual,[200 200],0);
    end
    sse = abs(sum(abs(sum(abs(sum(actual-flow)),2)),3));
    rss = sse/(size(actual,1)*size(actual,2));
    disp(file.name)
    disp(rss)
end
diary off;