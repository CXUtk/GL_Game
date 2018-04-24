#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_
class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void Draw();

	virtual void Update();
};
#endif // !_DRAWABLE_H_



