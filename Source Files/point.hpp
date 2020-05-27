#ifndef point_hpp
#define point_hpp



class Point
{
    private:
        int position_x,position_y;
    public:
        friend class Snake;
        Point(int x,int y);
        Point();
        void go_down();
        void go_up();
        void go_right();
        void go_left();
        virtual int pos_x(int j=0);
        virtual int pos_y(int j=0);
        void change_position_x(int x);
        void change_position_y(int y);
        void draw(int type);
        void set_cursor_position(int x,int y);
        Point& operator =(Point &received);
};

#endif // point_hpp
