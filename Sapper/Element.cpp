#include "Element.h"



Element::Element()
{
	colour = 110;
}
int Element::GetColour() {
	return colour;
}
void Element::SetColour(int value) {
	colour = value;
}
void Element::SetValue(int number) {
	elementValue = number;
}
int Element::GetValue() {
	return elementValue;
}
void Element::SetOpened(bool b) {
	openedValue = b;
}
bool Element::GetOpened() {
	return openedValue;
}


Element::~Element()
{
}
