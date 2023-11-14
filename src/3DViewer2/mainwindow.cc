#include "mainwindow.h"

#include <QFileDialog>

#include "./ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow(parent), controller_(controller), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Open File
  widget_ = new ModelRenderer(ui->centralwidget, *controller);
  widget_->setObjectName(QString::fromUtf8("widget"));
  widget_->setGeometry(QRect(20, 10, 1001, 711));

  ui->comboBoxVertexMode->setCurrentIndex(
      controller_->GetPropertyValue(PropertyKey::kVertexType).value<int>());

  ui->doubleSpinBoxSizeVertex->setValue(
      controller_->GetPropertyValue(PropertyKey::kVertexSize).value<double>());

  ui->comboBoxLineMode->setCurrentIndex(
      controller_->GetPropertyValue(PropertyKey::kLineType).value<int>());

  ui->doubleSpinBoxLineWidth->setValue(
      controller_->GetPropertyValue(PropertyKey::kLineWidth).value<double>());

  ui->comboBoxProection->setCurrentIndex(
      controller_->GetPropertyValue(PropertyKey::kProection).value<int>());

  connect(ui->openFileButton, &QPushButton::clicked, this,
          &MainWindow::handleOpenFileButtonClick);

  // Affine
  connect(ui->MoveX, &QPushButton::clicked, this, [this]() {
    handleAffinCommand(TypeCommand::kMoveX, ui->SpinBoxMoveX->value());
  });

  connect(ui->MoveY, &QPushButton::clicked, this, [this]() {
    handleAffinCommand(TypeCommand::kMoveY, ui->SpinBoxMoveY->value());
  });

  connect(ui->MoveZ, &QPushButton::clicked, this, [this]() {
    handleAffinCommand(TypeCommand::kMoveZ, ui->SpinBoxMoveZ->value());
  });

  connect(ui->RotateX, &QPushButton::clicked, this, [this]() {
    handleAffinCommand(TypeCommand::kRotateX, ui->SpinBoxRotateX->value());
  });

  connect(ui->RotateY, &QPushButton::clicked, this, [this]() {
    handleAffinCommand(TypeCommand::kRotateY, ui->SpinBoxRotateY->value());
  });

  connect(ui->RotateZ, &QPushButton::clicked, this, [this]() {
    handleAffinCommand(TypeCommand::kRotateZ, ui->SpinBoxRotateZ->value());
  });

  connect(ui->Scaling, &QPushButton::clicked, this, [this]() {
    handleAffinCommand(TypeCommand::kScale, ui->SpinBoxScaling->value());
  });

  connect(ui->Cancel, &QPushButton::clicked, this, &MainWindow::handleCancel);

  connect(ui->Reset, &QPushButton::clicked, this, &MainWindow::handleReset);

  // Custom

  connect(ui->doubleSpinBoxSizeVertex,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
            handleChangeProperties(
                PropertyKey::kVertexSize,
                static_cast<float>(ui->doubleSpinBoxSizeVertex->value()));
          });
  connect(ui->doubleSpinBoxLineWidth,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
            handleChangeProperties(
                s21::PropertyKey::kLineWidth,
                static_cast<float>(ui->doubleSpinBoxLineWidth->value()));
          });
  connect(ui->comboBoxVertexMode,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            handleChangeProperties(PropertyKey::kVertexType, index);
          });
  connect(ui->comboBoxLineMode,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            handleChangeProperties(s21::PropertyKey::kLineType, index);
          });
  connect(ui->comboBoxProection,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            handleChangeProperties(s21::PropertyKey::kProection, index);
          });
  connect(ui->comboBoxLineMode,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            handleChangeProperties(s21::PropertyKey::kLineType, index);
          });
  connect(ui->comboBoxProection,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            handleChangeProperties(s21::PropertyKey::kProection, index);
          });

  connect(ui->btnSetVertexColor, &QPushButton::clicked, this, [this]() {
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      handleChangeProperties(PropertyKey::kVertexColor, color);
    }
  });
  connect(ui->btnSetBackGroundColor, &QPushButton::clicked, this, [this]() {
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      handleChangeProperties(PropertyKey::kBackGroundColor, color);
    }
  });

  connect(ui->doubleSpinBoxLineWidth,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
            handleChangeProperties(
                PropertyKey::kLineWidth,
                static_cast<float>(ui->doubleSpinBoxLineWidth->value()));
          });

  connect(ui->comboBoxLineMode,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            handleChangeProperties(PropertyKey::kLineType, index);
          });

  connect(ui->btnSetLineColor, &QPushButton::clicked, this, [this]() {
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      handleChangeProperties(PropertyKey::kLineColor, color);
    }
  });

  connect(ui->btnRecordBmp, &QPushButton::clicked, this,
          [this]() { MainWindow::handleChooseRecord(TypeRecord::kBmp); });

  connect(ui->btnRecordJpeg, &QPushButton::clicked, this,
          [this]() { MainWindow::handleChooseRecord(TypeRecord::kJpeg); });

  connect(ui->btnRecordGif, &QPushButton::clicked, this,
          [this]() { MainWindow::handleChooseRecord(TypeRecord::kGif); });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::handleOpenFileButtonClick() {
  QString path = QFileDialog::getOpenFileName(this, tr("Open file"),
                                              QDir::homePath(), tr("*"));
  controller_->OpenFile(path.toStdString());
  controller_->SendObjectInfo(path.toStdString());
  ui->labelOpenFile->setText(path);
  ui->labelCountVert->setText(
      QString::number(controller_->GetObjectInfo().GetVertexCount()));
  ui->labelCountFacet->setText(
      QString::number(controller_->GetObjectInfo().GetFacetCount()));
  ui->labelFileName->setText(
      QString::fromStdString(controller_->GetObjectInfo().GetPath()));
}

void MainWindow::handleAffinCommand(TypeCommand key, double value) {
  controller_->SendAffineCommand(TypeDataCommand(key, value));
  widget_->update();
}

void MainWindow::handleCancel() {
  controller_->SendCancelCommand();
  widget_->update();
}

void MainWindow::handleReset() {
  controller_->SendReset();
  widget_->update();
}

void MainWindow::handleChangeProperties(PropertyKey key, std::any value) {
  const std::type_index &valueType = value.type();
  auto it = handlers_.find(valueType);
  if (it != handlers_.end()) {
    it->second(value, key, this);
  }
  widget_->update();
}

void MainWindow::handleChooseRecord(TypeRecord key) {
  controller_->ChooseRecord(widget_, key);
}

}  // namespace s21
