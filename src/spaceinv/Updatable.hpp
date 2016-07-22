#pragma once

class Updatable {
public:
    virtual ~Updatable() {}
    virtual void update(const float seconds) = 0;
};
