function [] = showConfiguration(polymerName, step)

%polymerName  = '5dn7'
%step = 0;

fileName = sprintf('../results/%s_configurations.dat',polymerName);

%--------count number of sites-------------
linesInBlock = 0;
prevLineIsEmpty = false;
fp = fopen(fileName);

emptyLine = sprintf('\n');

string = fgets(fp);

blockNum = 1;
lineNum=1;

while ischar(string)
    
    if strcmp(emptyLine, string)
   
        if(~prevLineIsEmpty)
            N{blockNum}=lineNum - 1;
            blockNum = blockNum + 1;
            lineNum = 1;
        end
        prevLineIsEmpty = true;
    else
        lineNum = lineNum + 1;
        prevLineIsEmpty = false;
    end
    string = fgets(fp);
end
fclose(fp);
blockNum = blockNum-1;
%-----------------end----------------------

% read file
fp = fopen(fileName);

for i=1:blockNum
    N{i};
    B{i}=fscanf(fp, '%g %g %g', [3 N{i}]);
    B{i}=B{i}';
end
fclose(fp);

axis equal;
axis on;

% color scheme
linkColorR = rand;
linkColorG = rand;
linkColorB = rand;

atomColorR = rand;
atomColorG = rand;
atomColorB = rand;

% drawing
k = step+1;
fprintf('Number of monomers: %d\n',N{k});

for i=2:N{k}-1
    axis on;
    axis equal; 
    view([45, -45, 45]);
    h1=line([B{k}(i,1) B{k}(i+1,1)],[B{k}(i,2) B{k}(i+1,2)],[B{k}(i,3) B{k}(i+1,3)],'LineStyle','-','LineWidth',3,'Color',[linkColorR linkColorG linkColorG]);    
    h2=stem3(B{k}(i,1),B{k}(i,2),B{k}(i,3),'LineStyle','none','Marker','o', 'MarkerFaceColor',[atomColorR atomColorG atomColorB],'MarkerEdgeColor', [0 0 0],'MarkerSize',10);
    hold on;
end
axis equal; 
line([B{k}(1,1) B{k}(2,1)],[B{k}(1,2) B{k}(2,2)],[B{k}(1,3) B{k}(2,3)],'LineStyle','-','LineWidth',3,'Color',[linkColorR linkColorG linkColorG]);
line([B{k}(2,1) B{k}(3,1)],[B{k}(2,2) B{k}(3,2)],[B{k}(2,3) B{k}(3,3)],'LineStyle','-','LineWidth',3,'Color',[linkColorR linkColorG linkColorG]);

clear
end %end of function