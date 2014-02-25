files = dir('*.txt');
orig = checkerboard > .5;
for file = files'
    flow = load(file.name);
    flow = reshape(flow,sqrt(size(flow,1)),sqrt(size(flow,1)),2);
    flow(:,:,1)=flow(:,:,1)';
    flow(:,:,2)=flow(:,:,2)';
    flow = flow(158:237,158:237,:);
    if strfind(file.name, 'translate') == 1
        tform=affine2d([1 0 0; 0 1 0; -5 5 1]);
        translate = velfield(orig, tform);
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
    elseif strfind(file.name, 'fracture') == 1
        continue;
        %tform=affine2d([]);
        %actual = velfield(orig, tform);
    end
    sse = abs(sum(sum(sum(actual-flow),2),3));
    disp(file.name)
    disp(sse)
end