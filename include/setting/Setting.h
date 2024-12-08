//
// Created by arunc on 27/10/2024.
//

#ifndef SETTING_H
#define SETTING_H


class Setting {
public:
    static Setting &getInstance() {
        static Setting instance; // Instanță statică
        return instance;
    }

    bool enableLineRender = false;

private:
    Setting() {
    }


    Setting(const Setting &) = delete;

    Setting &operator=(const Setting &) = delete;
};


#endif //SETTING_H
