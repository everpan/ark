#include "ArkEditor.h"

static const QString testSQL = "insert overwrite table t_sd_mobile_assist_mid_appid partition(ds=%YYYYMMDD%) \n"
                        "select  a.fapp_id, \n"
                        "        a.fdload_num,\n"
                        "        a.fdone_user_num,\n"
                        "        if(b.fclick_user_num>0,b.fclick_user_num,0), \n"
                        "        if(c.finstall_user_num>0,c.finstall_user_num,0), \n"
                        "        a.fip_num, \n"
                        "        a.fevil_ip_num,\n"
                        "        a.fsuspicious_ip_num,\n"
                        "        a.finternetbar_ip_num, \n"
                        "        a.fagent_ip_num, \n"
                        "        a.fqua_num,\n"
                        "        a.fapp_name, \n"
                        "        a.fimei_num\n"
                        "from \n"
                        "(\n"
                        "    select  fapp_id, \n"
                        "            fapp_name, \n"
                        "            count(1) fdload_num, \n"
                        "            count(distinct fguid) fdone_user_num,\n"
                        "            count(distinct fclient_ip) fip_num,\n"
                        "            count(distinct if(fip_evil_rank>1,fclient_ip,NULL)) fevil_ip_num,\n"
                        "            count(distinct if(fip_evil_rank=1,fclient_ip,NULL)) fsuspicious_ip_num,\n"
                        "            count(distinct if(fip_property|1==fip_property,fclient_ip,NULL)) finternetbar_ip_num,\n"
                        "            count(distinct if(fip_property|16==fip_property,fclient_ip,NULL)) fagent_ip_num, \n"
                        "            count(distinct fqua) fqua_num, \n"
                        "            count(distinct fimei) fimei_num\n"
                        "    from t_sh_mobile_assist_raw_download \n"
                        "    where ds>=%YYYYMMDD%00 and ds<=%YYYYMMDD%23\n"
                        "    group by fapp_id,fapp_name \n"
                        ")a \n"
                        "left join\n"
                        "(\n"
                        "    select fapp_id,count(distinct fguid) fclick_user_num \n"
                        "    from t_sh_mobile_assist_useraction \n"
                        "    where ds>=%YYYYMMDD%00 and ds<=%YYYYMMDD%23 and faction_id=900 \n"
                        "    group by fapp_id \n"
                        ")b on a.fapp_id=b.fapp_id\n"
                        "left join\n"
                        "(\n"
                        "    select fapp_id,count(distinct fguid)finstall_user_num\n"
                        "    from t_sh_mobile_assist_raw_appinstall \n"
                        "    where ds>=%YYYYMMDD%00 and ds<=%YYYYMMDD%23\n"
                        "    group by fapp_id \n"
                        ")c on a.fapp_id=c.fapp_id\n";

ArkEditor::ArkEditor(QWidget *parent) : QsciScintilla(parent)
{
    QFont font = QFont();
    font.setFamily("Consolas");
    font.setFixedPitch(true);
    font.setPointSize(10);
    QFontMetrics fm(font);
    setMarginLineNumbers(0,true);
    setMarginWidth(0,fm.width("00000") + 5);
    //列宽线
    setEdgeMode(QsciScintilla::EdgeLine);
    setEdgeColumn(80);
    setEdgeColor(QColor("#FF0000"));

    //
    setFolding(QsciScintilla::BoxedTreeFoldStyle);
    setBraceMatching(QsciScintilla::SloppyBraceMatch);

    //
    setCaretLineVisible(true);
    setCaretLineBackgroundColor(QColor("#E8E8FF"));

    setMarginsBackgroundColor(QColor("#333333"));
    setMarginsForegroundColor(QColor("#CCCCCC"));

    //folding margin colors (foreground,background);
    setFoldMarginColors(QColor("#99CC66"),QColor("#333300"));

    //utf8
    setUtf8(true);
    _lang = NoLang;

}
ArkEditor::~ArkEditor(){

}


void ArkEditor::openFile(const QString& filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //todo error report
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF8");

    setText(in.readAll());
    setModified(false);
    file.close();
    _filename = filename;
    emit changeFileName(filename);
}
void ArkEditor::saveFile(const QString& filename){
    if(!isModified()) return; //未做修改，不保存
    bool isChangeFileName = false;
    if(!filename.isEmpty()){
        //save as
        if(_filename != filename){
            _filename = filename;
            isChangeFileName = true;
        }
    }
    do{
        if(_filename.isEmpty()){
            QString file = QFileDialog::getSaveFileName(this,tr("Save File to ..."),"",
                                                        tr("SQL Files (*.sql *.hql);;Bash(*.sh);;Python(*.py)"));
            _filename = file;
            if(_filename.isEmpty()){
                QMessageBox::StandardButton ret = QMessageBox::question(this,tr("Save?"),tr("Save \"new file\"?"));
                if(ret == QMessageBox::No){
                    clear();
                    setModified(false);
                    return;
                }
                //break;
            }else{
                qDebug() << "save file to:" << _filename;
                isChangeFileName = true;
            }
        }
    }while(1);

    QFile file(_filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        //todo error report
        qDebug() << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << " can't open file:" << _filename << " for writeonly";
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF8");
    out << text();
    setModified(false);
    file.close();
    if(isChangeFileName){
        emit changeFileName(_filename);
    }
}
const QString& ArkEditor::fileName(){
    return _filename;
}
QFileInfo ArkEditor::getFileInfo(){
    return QFileInfo(_filename);
}
void ArkEditor::setLanguage(ArkEditorLANG lang){
    QsciLexer * newlexer = NULL;
    switch (lang) {
    case SQL:
        newlexer = new QsciLexerSQL(this);
        break;
    case PYTHON:
        newlexer = new QsciLexerPython(this);
        break;
    case BASH:
        newlexer = new QsciLexerBash(this);
    default:
        return;
        //break;
    }
    _lang = lang;
    //不确定是否要自我管理，通用做法
    QsciLexer * oldlexer = lexer();
    if(oldlexer) oldlexer->deleteLater();
    setLexer(newlexer);
}
