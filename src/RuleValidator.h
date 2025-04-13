#ifndef RULEVALIDATOR_H
#define RULEVALIDATOR_H

#include <QValidator>
#include <QRegularExpression>

class RuleValidator : public QValidator
{
    QRegularExpression pattern;
public:
    RuleValidator(QObject *parent = nullptr) : QValidator(parent) {
        pattern.setPattern("[^LFRU]");
    }

    State validate(QString &str, int &) const {
        str = str.toUpper();
        if (str.contains(pattern))
            return Invalid;
        return Acceptable;
    }
};

#endif // RULEVALIDATOR_H
