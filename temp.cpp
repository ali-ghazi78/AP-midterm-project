auto move_right_down = [&]() {
        auto it = std::find(v.begin(), v.end(), 0);
        int x = it - v.begin();
        int y = x / 3;
        x = x % 3;
        x++;
        while(x<=2)
        {
            std::swap(v[it - v.begin()],v[y*3+x]);
            it = std::next(v.begin(), y*3+x);
            x++ ;
        }
        x--;
        y++;
        while(y<=2)
        {
            std::swap(v[it - v.begin()],v[y*3+x]);
            it = std::next(v.begin(), y*3+x);
            y++ ;
        }
        
    };
    //