close all

orig=checkerboard>.5;
%orig=imresize(imnoise(ones(20),'gaussian'),4);
%orig=imresize(imnoise(ones(20),'salt & pepper'),4);

imshow(padarray(orig,[200 200],255));

tform=affine2d([1 0 0; .5 1 0; 0 0 1]);
writerObj = VideoWriter('skew.avi');
open(writerObj);
frame=getframe;
writeVideo(writerObj,frame);
s=imwarp(orig,tform,'FillValue',255);
for i=1:10
    dr=size(s,1)-size(orig,1);
    dc=size(s,2)-size(orig,2);
    imshow(padarray(s,[200-dr/2 200-dc/2],255));
    frame=getframe;
    writeVideo(writerObj,frame);
    s=imwarp(s,tform,'FillValue',255);
end
close(writerObj);

theta=1;
tform=affine2d([cosd(theta) -sind(theta) 0; sind(theta) cosd(theta) 0; 0 0 1]);
writerObj = VideoWriter('rotate.avi');
open(writerObj);
imshow(padarray(orig,[200 200],255));
frame=getframe;
writeVideo(writerObj,frame);
r=imwarp(orig,tform,'FillValue',255);
for i=1:10
    dr=size(r,1)-size(orig,1);
    dc=size(r,2)-size(orig,2);
    imshow(padarray(r,[200-dr/2 200-dc/2],255));
    frame=getframe;
    writeVideo(writerObj,frame);
    r=imwarp(r,tform,'FillValue',255);
end
close(writerObj);

writerObj = VideoWriter('translate.avi');
open(writerObj);
imshow(padarray(orig,[200 200],255));
frame=getframe;
writeVideo(writerObj,frame);
for i=1:10
    t=padarray(orig,[200-5*i 200-5*i],255,'pre');
    t=padarray(t,[200+5*i 200+5*i],255,'post');
    imshow(t);
    frame=getframe;
    writeVideo(writerObj,frame);
end
close(writerObj);

writerObj = VideoWriter('scale.avi');
open(writerObj);
for i=1:10
    scale=imresize(orig,(i+1)/2);
    dr=size(scale,1)-size(orig,1);
    dc=size(scale,2)-size(orig,2);
    scale=padarray(scale,[200-dr/2 200-dc/2],255);
    imshow(scale);
    frame=getframe;
    writeVideo(writerObj,frame);
end
close(writerObj);

writerObj = VideoWriter('fracture.avi');
open(writerObj);
imshow(padarray(orig,[200 200],255));
frame=getframe;
writeVideo(writerObj,frame);
for i=1:10
    frac=cat(2,padarray(orig(:,1:size(orig,2)/2),[2*i 0],255,'pre'), padarray(orig(:,((size(orig,2)/2)+1):end),[2*i 0],255,'post'));
    dr=size(frac,1)-size(orig,1);
    dc=size(frac,2)-size(orig,2);
    frac=padarray(frac,[200-dr/2 200-dc/2],255);
    imshow(frac);
    frame=getframe;
    writeVideo(writerObj,frame);
end
close(writerObj);

close all