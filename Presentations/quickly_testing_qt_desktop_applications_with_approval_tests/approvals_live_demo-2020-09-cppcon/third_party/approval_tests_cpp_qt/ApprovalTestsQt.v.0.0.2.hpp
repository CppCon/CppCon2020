// ApprovalTests.cpp.Qt version v.0.0.2
// More information at: https://github.com/approvals/ApprovalTests.cpp.Qt


// ******************** From: ApprovalTestsQt.hpp
#ifndef APPROVAL_TESTS_QT_CPP_APPROVALS_HPP
#define APPROVAL_TESTS_QT_CPP_APPROVALS_HPP

// This file is machine-generated. Do not edit.


// ******************** From: LoadApprovals.h
#ifndef APPROVALTESTS_CPP_QT_LOADAPPROVALS_H
#define APPROVALTESTS_CPP_QT_LOADAPPROVALS_H

// Never #include "ApprovalTests.hpp" directly in this project:
// #include "ApprovalTestsQt/integrations/LoadApprovals.h" instead

// <SingleHpp unalterable>
// clang-format off
#if defined(APPROVALS_CATCH_QT)
    #define CATCH_CONFIG_RUNNER
    #include <catch2/catch.hpp>
    #define APPROVALS_CATCH_EXISTING_MAIN
#endif
// clang-format on

#include <ApprovalTests.hpp>
// </SingleHpp>

#endif //APPROVALTESTS_CPP_QT_LOADAPPROVALS_H

// ******************** From: QTableViewWriter.h
#ifndef APPROVALTESTS_CPP_QT_QTABLEVIEWWRITER_H
#define APPROVALTESTS_CPP_QT_QTABLEVIEWWRITER_H


#include <QTableView>
#include <QFile>
#include <QTextStream>

namespace ApprovalTestsQt
{
    class QTableViewWriter : public ApprovalTests::ApprovalWriter
    {
    public:
        explicit QTableViewWriter(const QTableView& tableView,
                                  std::string fileExtensionWithDot = ".tsv")
            : tableView_(tableView), fileExtensionWithDot_(fileExtensionWithDot)
        {
        }

        std::string getFileExtensionWithDot() const override
        {
            return fileExtensionWithDot_;
        }

        void write(std::string path) const override
        {
            // Code adapted from https://stackoverflow.com/a/46236672/104370
            QFile file(QString::fromStdString(path));

            QString separator("\t");
            QAbstractItemModel* model = tableView_.model();
            if (file.open(QFile::WriteOnly | QFile::Truncate))
            {
                QTextStream data(&file);
                QStringList strList;
                for (int i = 0; i < model->columnCount(); i++)
                {
                    QVariant variant =
                        model->headerData(i, Qt::Horizontal, Qt::DisplayRole);
                    strList.append(quoteString(variant));
                }
                data << strList.join(separator) << "\n";
                for (int i = 0; i < model->rowCount(); i++)
                {
                    strList.clear();
                    for (int j = 0; j < model->columnCount(); j++)
                    {
                        QVariant variant = model->data(model->index(i, j));
                        strList.append(quoteString(variant));
                    }
                    data << strList.join(separator) + "\n";
                }
                file.close();
            }
            else
            {
                throw std::runtime_error("Unable to table write to file " + path);
            }
        }

        void cleanUpReceived(std::string receivedPath) const override
        {
            remove(receivedPath.c_str());
        }

    private:
        QString quoteString(const QVariant& data) const
        {
            if (data.toString().length() > 0)
                return "\"" + data.toString() + "\"";
            else
                return "";
        }

    private:
        const QTableView& tableView_;
        std::string fileExtensionWithDot_;
    };
} // namespace ApprovalTestsQt

#endif //APPROVALTESTS_CPP_QT_QTABLEVIEWWRITER_H

// ******************** From: QImageApprovalWriter.h
#ifndef APPROVALTESTS_CPP_QT_QIMAGEAPPROVALWRITER_H
#define APPROVALTESTS_CPP_QT_QIMAGEAPPROVALWRITER_H


#include <QImage>

namespace ApprovalTestsQt
{
    class QImageApprovalWriter : public ApprovalTests::ApprovalWriter
    {
    public:
        explicit QImageApprovalWriter(QImage image,
                                      std::string fileExtensionWithDot = ".png")
            : image_(image), fileExtensionWithDot_(fileExtensionWithDot)
        {
        }

        std::string getFileExtensionWithDot() const override
        {
            return fileExtensionWithDot_;
        }

        void write(std::string path) const override
        {
            // Have to convert std::string to QString
            image_.save(QString::fromStdString(path));
        }

        void cleanUpReceived(std::string receivedPath) const override
        {
            remove(receivedPath.c_str());
        }

    private:
        QImage image_;
        std::string fileExtensionWithDot_;
    };
} // namespace ApprovalTestsQt

#endif //APPROVALTESTS_CPP_QT_QIMAGEAPPROVALWRITER_H

// ******************** From: ApprovalTestsQtVersion.h

#define APPROVAL_TESTS_QT_VERSION_MAJOR 0
#define APPROVAL_TESTS_QT_VERSION_MINOR 0
#define APPROVAL_TESTS_QT_VERSION_PATCH 2
#define APPROVAL_TESTS_QT_VERSION_STR "0.0.2"

#define APPROVAL_TESTS_QT_VERSION                                                        \
    (APPROVAL_TESTS_QT_VERSION_MAJOR * 10000 + APPROVAL_TESTS_QT_VERSION_MINOR * 100 +   \
     APPROVAL_TESTS_QT_VERSION_PATCH)

// ******************** From: ApprovalsQt.h
#ifndef APPROVALTESTS_CPP_QT_APPROVALSQT_H
#define APPROVALTESTS_CPP_QT_APPROVALSQT_H


namespace ApprovalTestsQt
{
    inline void
    verifyQImage(const QImage& image,
                 const ApprovalTests::Options& options = ApprovalTests::Options())
    {
        QImageApprovalWriter image_writer(image);
        ApprovalTests::Approvals::verify(image_writer, options);
    }

    inline void
    verifyQTableView(const QTableView& tableWidget,
                     const ApprovalTests::Options& options = ApprovalTests::Options())
    {
        QTableViewWriter table_writer(tableWidget);
        ApprovalTests::Approvals::verify(table_writer, options);
    }
} // namespace ApprovalTestsQt

#endif //APPROVALTESTS_CPP_QT_APPROVALSQT_H

// ******************** From: QImageApprovalComparator.h
#ifndef APPROVALTESTS_CPP_QT_QIMAGEAPPROVALCOMPARATOR_H
#define APPROVALTESTS_CPP_QT_QIMAGEAPPROVALCOMPARATOR_H

#include <QImage>

namespace ApprovalTestsQt
{
    class QImageApprovalComparator : public ApprovalTests::ApprovalComparator
    {
    public:
        bool contentsAreEquivalent(std::string receivedPath,
                                   std::string approvedPath) const override
        {
            const QImage receivedImage(QString::fromStdString(receivedPath));
            const QImage approvedImage(QString::fromStdString(approvedPath));
            return receivedImage == approvedImage;
        }
    };
} // namespace ApprovalTestsQt

#endif //APPROVALTESTS_CPP_QT_QIMAGEAPPROVALCOMPARATOR_H

// ******************** From: Catch2QtApprovals.h
#ifndef APPROVALTESTS_CPP_QT_CATCH2QTAPPROVALS_H
#define APPROVALTESTS_CPP_QT_CATCH2QTAPPROVALS_H

#if defined(APPROVALS_CATCH_QT)

#include <QApplication>
#include <QApplication>

int main(int argc, char* argv[])
{
    // Any tests that create Qt widgets require a QApplication
    // to already have been created, to avoid the following message:
    //  QWidget: Must construct a QApplication before a QWidget
    // So we follow the lead of the Qt Test framework and create it in main().
    QApplication app(argc, argv);

    // When comparing PNG files, get Qt to read the two image files and
    // compare the QImage objects, instead of using the built-in
    // character-based file comparison, which may fail for two
    // exactly equivalent .png files.
    auto pngComparatorDisposer =
        ApprovalTests::FileApprover::registerComparatorForExtension(
            ".png", std::make_shared<ApprovalTestsQt::QImageApprovalComparator>());

    // your existing setup...
    int result = Catch::Session().run(argc, argv);

    // your existing clean-up...
    return result;
}
#endif // APPROVALS_CATCH_QT

#endif //APPROVALTESTS_CPP_QT_CATCH2QTAPPROVALS_H

// ******************** From: Catch2QtStringMaker.h
#ifndef APPROVALTESTS_CPP_QT_CATCH2QTSTRINGMAKER_H
#define APPROVALTESTS_CPP_QT_CATCH2QTSTRINGMAKER_H

#ifdef CATCH_VERSION_MAJOR
#include <QColor>
#include <QTest>
#include <QStringBuilder>

namespace Catch
{
    template <> struct StringMaker<QColor>
    {
        static std::string convert(QColor const& color)
        {
            // clang-format off
            const QString result = "(" %
                                   QString::number(color.redF()) % ", " %
                                   QString::number(color.greenF()) % ", " %
                                   QString::number(color.blueF()) %
                                   "), alpha = " %
                                   QString::number(color.alphaF(), 'g', 20);
            // clang-format on
            return result.toStdString();
        }
    };

    // This adds support for all the types that can be stringified with Qt Test:
    // https://doc.qt.io/qt-5/qtest.html#toString
    template <class QtCoreType> struct StringMaker<QtCoreType>
    {
        static std::string convert(QtCoreType const& object)
        {
            return QTest::toString(object);
        }
    };

    template <> struct StringMaker<QString>
    {
        static std::string convert(QString const& string)
        {
            return string.toStdString();
        }
    };
} // namespace Catch
#endif // CATCH_VERSION_MAJOR

#endif //APPROVALTESTS_CPP_QT_CATCH2QTSTRINGMAKER_H

#endif // APPROVAL_TESTS_QT_CPP_APPROVALS_HPP
