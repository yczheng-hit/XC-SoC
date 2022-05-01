#ifndef IMAGE_H
#define IMAGE_H

template <class PIXEL>
class IMAGE
{
protected:
	unsigned char *m_buf;
	void allocbuf(int h, int w);
	void deallocb(void);

public:
	int m_height, m_width;
	PIXEL **m_img;
	PIXEL *m_data;

	IMAGE(int h, int w);
	IMAGE(IMAGE *imgp);
	~IMAGE() { delete[] m_buf; }
	long size(void) const { return m_height * m_width; }
	IMAGE *crop(int x, int y, int h, int w);

	void zeroize(void);
	IMAGE *copy(void);
	void flipy(void);
	void flipx(void);

	int height(void) const { return m_height; }
	int cols(void) const { return m_height; }
	int width(void) const { return m_width; }
	int rows(void) const { return m_width; }
};

typedef IMAGE<unsigned char> UCIMAGE, *PIMAGE;
typedef IMAGE<int> IIMAGE, *PIIMAGE;
typedef IMAGE<double> DIMAGE, *PDIMAGE;
#ifdef COMPLEX_H
typedef IMAGE<COMPLEX> CIMAGE, *PCIMAGE;
#endif

#endif
