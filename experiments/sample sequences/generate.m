close all

orig=checkerboard>.5;
subsampling = 16;
%orig=imresize(imnoise(ones(20),'gaussian'),4);
%orig=imresize(imnoise(ones(20),'salt & pepper'),4);

imshow(padarray(orig,[200 200],255));

tform=affine2d([1 0 0; .5 1 0; 0 0 1]);
writerObj = VideoWriter('skew16.avi');
open(writerObj);
frame=uint8(padarray(orig,[200 200],255).*255);
frame=frame(1:subsampling:end,1:subsampling:end);
writeVideo(writerObj,frame);
s=imwarp(orig,tform,'FillValue',255);
for i=1:10
    dr=floor(size(s,1)-size(orig,1));
    dc=floor(size(s,2)-size(orig,2));
    frame=uint8(padarray(s,[200-dr/2 200-dc/2],255).*255);
    frame=frame(1:subsampling:end,1:subsampling:end);
    writeVideo(writerObj,frame);
    s=imwarp(s,tform,'FillValue',255);
end
close(writerObj);

theta=1;
tform=affine2d([cosd(theta) -sind(theta) 0; sind(theta) cosd(theta) 0; 0 0 1]);
writerObj = VideoWriter('rotate16.avi');
open(writerObj);
frame=uint8(padarray(orig,[200 200],255).*255);
frame=frame(1:subsampling:end,1:subsampling:end);
writeVideo(writerObj,frame);
r=imwarp(orig,tform,'FillValue',255);
for i=1:10
    dr=size(r,1)-size(orig,1);
    dc=size(r,2)-size(orig,2);
    frame=uint8(padarray(r,[200-dr/2 200-dc/2],255).*255);
    frame=frame(1:subsampling:end,1:subsampling:end);
    writeVideo(writerObj,frame);
    r=imwarp(r,tform,'FillValue',255);
end
close(writerObj);

writerObj = VideoWriter('translate16.avi');
open(writerObj);
frame=uint8(padarray(orig,[200 200],255).*255);
frame=frame(1:subsampling:end,1:subsampling:end);
writeVideo(writerObj,frame);
for i=1:10
    t=padarray(orig,[200-5*i 200-5*i],255,'pre');
    t=padarray(t,[200+5*i 200+5*i],255,'post');
    frame=uint8(t.*255);
    frame=frame(1:subsampling:end,1:subsampling:end);
    writeVideo(writerObj,frame);
end
close(writerObj);

writerObj = VideoWriter('scale16.avi');
open(writerObj);
for i=1:10
    scale=imresize(orig,(i+1)/2);
    dr=size(scale,1)-size(orig,1);
    dc=size(scale,2)-size(orig,2);
    scale=padarray(scale,[200-dr/2 200-dc/2],255);
    frame=uint8(scale.*255);
    frame=frame(1:subsampling:end,1:subsampling:end);
    writeVideo(writerObj,frame);
end
close(writerObj);

writerObj = VideoWriter('fracture16.avi');
open(writerObj);
frame=uint8(padarray(orig,[200 200],255).*255);
frame=frame(1:subsampling:end,1:subsampling:end);
writeVideo(writerObj,frame);
for i=1:11
    frac=cat(2,padarray(orig(:,1:size(orig,2)/2),[2*i 0],255,'pre'), padarray(orig(:,((size(orig,2)/2)+1):end),[2*i 0],255,'post'));
    dr=size(frac,1)-size(orig,1);
    dc=size(frac,2)-size(orig,2);
    frac=padarray(frac,[200-dr/2 200-dc/2],255);
    frame=uint8(frac.*255);
    frame=frame(1:subsampling:end,1:subsampling:end);
    writeVideo(writerObj,frame);
end
close(writerObj);

close all