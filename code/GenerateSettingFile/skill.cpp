#include <QtCore/QtCore>
#include <QImage>

void testSkill(const QString &inFile)
{
	qDebug() << __FUNCTION__ << inFile;

	QFile file(inFile);
	if (!file.open(QIODevice::ReadOnly))
	{
		return;
	}

	QImage img;
	quint32 ID, lv, spell1, spell2, spell3, cd, times, damage1, damage2, damage3, buff;
	QString name, descr;

	QDataStream out(file.readAll());
	while (!out.atEnd())
	{
		out >> ID >> name >> img >> lv >> spell1 >> spell2 >> spell3 >> cd
			>> times >> damage1 >> damage2 >> damage3 >> buff >> descr;

		qDebug() << ID << name << img.isDetached() << lv << spell1 << spell2 << spell3 << cd
			<< times << damage1 << damage2 << damage3 << buff << descr;
	}

	file.close();
}

void Skill(const QString &inFile, const QString &outFile)
{
	qDebug() << __FUNCTION__ << inFile << outFile;

	QFile Rfile(inFile);
	if (!Rfile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "open " << inFile << "error.";
		return;
	}

	QFile Wfile(outFile);
	if (!Wfile.open(QIODevice::WriteOnly))
	{
		qDebug() << "open " << outFile << "error.";
		return;
	}

	QString strTmp;
	QStringList list;

	QImage img;
	quint32 i, ID, photo, lv, spell[3], cd, times, damage[3], buff;
	QString name, descr, strImgPath;

	QDataStream iData(&Wfile);

	Rfile.readLine(1000);		//第一行是标题
	while (!Rfile.atEnd())
	{
		strTmp = Rfile.readLine(1000);
		if (strTmp.isEmpty() || strTmp.isNull())
		{
			//防止文件尾部有空白行。
			break;
		}
		list = strTmp.split("\t");
		i = 0;
		ID = list.at(i++).toUInt();
		name = list.at(i++);
		photo = list.at(i++).toUInt();

		strImgPath = QString("./Resources/skill/");
		strImgPath += QString::number(photo) + QString(".png");

		if (!QFile::exists(strImgPath))
		{
			qDebug() << "Cannot find file." << strImgPath;
			break;
		}
		img = QImage(strImgPath);
		if (img.isNull())
		{
			qDebug() << "No Head:" << strImgPath;
			break;
		}
		lv = list.at(i++).toUInt();
		spell[0] = list.at(i++).toUInt();
		spell[1] = list.at(i++).toUInt();
		spell[2] = list.at(i++).toUInt();
		cd = list.at(i++).toUInt();
		times = list.at(i++).toUInt();
		damage[0] = list.at(i++).toUInt();
		damage[1] = list.at(i++).toUInt();
		damage[2] = list.at(i++).toUInt();
		buff = list.at(i++).toUInt();
		descr = list.at(i++);

		iData << ID << name << img << lv << spell[0] << spell[1] << spell[2] << cd 
			<< times << damage[0] << damage[1] << damage[2] << buff << descr;
	}

	Rfile.close();
	Wfile.close();

	qDebug() << __FUNCTION__ << "run over";

	testSkill(outFile);
}