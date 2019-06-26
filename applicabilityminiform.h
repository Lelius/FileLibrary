#ifndef APPLICABILITYMINIFORM_H
#define APPLICABILITYMINIFORM_H

#include <QWidget>

namespace Ui {
class ApplicabilityMiniForm;
}

class ApplicabilityMiniForm : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicabilityMiniForm(QWidget *parent = nullptr);
    ~ApplicabilityMiniForm();

private:
    Ui::ApplicabilityMiniForm *ui;
};

#endif // APPLICABILITYMINIFORM_H
