#pragma once

class Module
{
protected:
    virtual void process();

public:
    virtual bool init();
    virtual void deinit();
    virtual void prepare();
    virtual void step();
};
