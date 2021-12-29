void func(int* a){
	*a += 5;
}
int main(){
	int n = 10;
	int j = n | func(&n);
	return 0;
}
