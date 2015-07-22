#include <iostream>
using namespace std;
enum class State{ooo,oco,ooc,occ,coo,cco,coc,ccc};

ostream&operator << (ostream&o, State d){
o << (int)d;
return o;
}

int main()
{

cout << " ooo " << State::ooo << " oco " << State::oco << " ooc " << State::ooc << " occ " << State::occ << " coo "  << State::coo << " cco " << State::cco << " coc " << State::coc << " ccc " << State::ccc << endl;
}
