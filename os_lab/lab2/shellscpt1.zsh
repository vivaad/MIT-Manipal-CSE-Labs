echo Q1
echo $HOME, $PATH 
echo $MAIL 
echo $USER, $SHELL, $TERM

echo Q2
firstname=Rakesh ……local variables
lastname=Sharma
echo $firstname $lastname
export lastname #..make “lastname” an envi var 
sh #....start a child shell
echo $firstname $lastname 
^D #....terminate child shell
echo $firstname $lastname 

echo q3
echo the name of this script is $0
echo the first argument is $1
echo a list of all the arguments is $*
echo this script places the date into a temporary file


