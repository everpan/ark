#ifndef ARKEDITOR_H
#define ARKEDITOR_H

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerbash.h>
#include <QFontMetrics>
#include <QFont>
#include <QColor>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include <QDebug>

class ArkEditor : public QsciScintilla
{
    Q_OBJECT
public:
    //ArkEditor();
    enum ArkEditorLANG{
        NoLang = 0,
        SQL,
        PYTHON,
        BASH
    };
    explicit ArkEditor(QWidget *parent = 0);
    virtual ~ArkEditor();

    void openFile(const QString& filename);
    void saveFile(const QString& filename = QString());
    const QString& fileName();
    QFileInfo getFileInfo();
    void setLanguage(ArkEditorLANG lang);
    ArkEditorLANG getLanguage(){return _lang;}
signals:
    void changeFileName(const QString & filename);
private:
    ArkEditorLANG _lang;
    QString _filename;
};

#endif // ARKEDITOR_H
