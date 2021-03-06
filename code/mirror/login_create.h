#ifndef LOGIN_CREATE_H
#define LOGIN_CREATE_H

#include <QDialog>
#include "ui_login_create.h"
#include "def_DataType.h"

class login_create : public QDialog
{
	Q_OBJECT

public:
	login_create(QWidget *parent = 0);
	~login_create();
	bool getCreateRes() { return bCreate; }

private:
	//�����浵
	bool CreateAccount(const QString &name);

	void changePhoto();

private slots:
	void on_btn_vocation_1_clicked();
	void on_btn_vocation_2_clicked();
	void on_btn_vocation_3_clicked();
	void on_btn_gender_m_clicked();
	void on_btn_gender_f_clicked();
	void on_btn_ok_clicked();
	void on_btn_quit_clicked();

private:
	Ui::login_create ui;
	Vocation m_vocation;
	int32_t m_gender;

	bool bCreate;


};

#endif // LOGIN_CREATE_H
