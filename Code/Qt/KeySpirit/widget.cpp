#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    keys["左键"] = MOUSEEVENTF_LEFTDOWN;
    keys["右键"] = MOUSEEVENTF_RIGHTDOWN;

    for(const auto& key : keys) {
        static int i = 0;
        ui->clickkey->insertItem(i, key.first);
        i++;
    }
}

Widget::~Widget()
{
    delete ui;
}

/**
 * 检测全局快捷键按下，通过成员变量status记录输入状态，从而开始或停止输入
 * @brief Widget::on_globalKey_clicked
 */
void Widget::on_globalKey_clicked()
{
    QString origin_press_time = ui->presstime->text();
    QString origin_release_time = ui->releasetime->text();
    int pretime, reltime;
    try {
        pretime = std::stoi(origin_press_time.toStdString());
        reltime = std::stoi(origin_release_time.toStdString());
    } catch (const std::invalid_argument& e) {
        std::cerr << "Failed: time not a number";
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Failed: number over range";
        return;
    }

    QString origin_clickkey_text = ui->clickkey->currentText();
    auto k = keys.find(origin_clickkey_text);
    if (k == keys.end()) {
        std::cerr << "Error: Not found key";
        exit(1);
    }

    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = k->second;
    KeyClickHandle(&input, pretime, reltime);
}

/**
 * 模拟用户的按键输入功能函数
 * @brief KeyClickHandle
 * @param key  需要模拟的按键
 * @param pretime  按压时长
 * @param reltime  松开间隔
 */
void Widget::KeyClickHandle(INPUT *input, int pretime, int reltime) {
    std::cout << "start click" << std::endl;
    SendInput(1, input, sizeof(INPUT));
    Sleep(pretime);

    input->mi.dwFlags = input->mi.dwFlags << 1;
    SendInput(1, input, sizeof(INPUT));
    Sleep(reltime);
    std::cout << "finish click" << std::endl;
}
