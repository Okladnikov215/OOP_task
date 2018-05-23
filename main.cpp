#pragma warning( push, 4 )  

#include <iostream>
#include "Container.h"
#include "Shapes.h"
#include "ShapeFactory.h"
/*
Спроектировать и реализовать шаблонный класс Container со следующими возможностями :
-добавить новый элемент в начало / конец;
-удалить первый / последний элемент;
-получить значение первого / последнего элемента;
-перебрать все элементы(не обязательно делать итератор);
-узнать кол - во элементов;
-проверить на пустоту;
-очистить.
*/

int main()
{
	Container<Shape *> shapes;
	for (int i = 0; i < 500; ++i)
	{
		shapes.addFirst(ShapeFactory::makeRandomShape());
	}

	std::cout << "ShapesCount: " << Shape::getCount() << std::endl;

	std::cout << "Shapes:" << std::endl;
	shapes.forEach(
		[](Shape * const & shape)
	{
		std::cout << shape->print() << std::endl;
	}
	);

	shapes.forEach(
		[](Shape * const & shape)
	{
		delete shape;
	}
	);

	std::cout << "ShapesCount: " << Shape::getCount() << std::endl;

	shapes.clean();

	return 0;

}