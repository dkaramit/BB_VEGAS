

for file in $(find . -regextype egrep -regex '.*\.hpp'); do
    perl -pe 's/VEGAS\_Template/template<class LD, int NDim, int NBin, int NBinInit, class RandEn>/g; 
    s/VEGAS\_Namespace/VEGAS<LD,NDim,NBin,NBinInit,RandEn>/g' $file >tmp 

    less tmp > $file       
done