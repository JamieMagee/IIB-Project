files = dir('*.avi')
for k=1:length(files)
  file = files(k).name;
  obj=mmreader(file);
  obj.read();
  imwrite(ans(:,:,:,5),strcat(file,'.png'))
end