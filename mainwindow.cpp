// TODO: MEMORY CELL MANUALLY CHANGE
// TODO: STARTING INDEX
// TODO: HALT
// TODO: Handle memory mapping for the screen (address 00)

/**
 * @file mainwindow.cpp
 * @brief Running the Machine and Linking between the UI and the application classes
*/

#include "mainwindow.h"

/**
 * @brief Constructor for MainWindow class. Initializes the UI and connects signals.
 *
 * @param parent Pointer to the parent widget.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_cpu = new cpu;

    connecting();
    decodingDisplay();
    memoryDisplay();
    updateMemoryDisplay();
    registerDisplay();
    updateRegisterDisplay();

    // Program counter Display
    ui->pCounter->setText(QString::number(cpu::m_programCounter));
}


/**
 * @brief Destructor for MainWindow class.
 *
 * This destructor is responsible for cleaning up the dynamically allocated memory for the UI.
 * It is called when the MainWindow object is destroyed.
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete m_cpu;
}


/**
 * @brief Connecting signals*/
void MainWindow::connecting(){
    connect(ui->openInstructionButton, &QPushButton::clicked, this,
            &MainWindow::onOpenInstructionFileClicked);
    connect(ui->excuteButton, &QPushButton::clicked, this,
            &MainWindow::on_execute_button_clicked);
    connect(ui->decodeButton, &QPushButton::clicked, this,
            &MainWindow::onDecodeButtonClicked);
    connect(ui->fetchButton, &QPushButton::clicked, this,
            &MainWindow::onFetchButtonClicked);
    connect(ui->clearMemoryButton, &QPushButton::clicked, this,
            &MainWindow::on_clearMemoryButton_clicked);
    connect(ui->clearRegButton, &QPushButton::clicked, this,
            &MainWindow::on_clearRegButton_clicked);

}




/**
 * @brief The decoding display section*/
void MainWindow::decodingDisplay(){
    ui->encodedInsMessage->setReadOnly(true);
    ui->opCodeDisplay->setReadOnly(true);
    ui->rDisplay->setReadOnly(true);
    ui->xDisplay->setReadOnly(true);
    ui->yDisplay->setReadOnly(true);
}


/**
 * @brief setting memory display section*/
void MainWindow::memoryDisplay() {
    ui->memoryDisplay->setRowCount(256);
    ui->memoryDisplay->setColumnCount(4);
    QStringList headers = {"Address", "Binary", "Hex", "Int"};
    ui->memoryDisplay->setHorizontalHeaderLabels(headers);

    // Setting memory display properties
    ui->memoryDisplay->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->memoryDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memoryDisplay->verticalHeader()->setVisible(false);
}

void MainWindow::updateMemoryDisplay() {
    for (int i = 0; i < 256; ++i) {
        // Address column (display as hex)
        QString address = QString::number(i, 16).toUpper().rightJustified(2, '0');
        ui->memoryDisplay->setItem(i, 0, new QTableWidgetItem(address));

        // Binary column (initialize with 8-bit binary representation)
        QString binaryValue = QString("%1").arg(m_cpu->m_memory->getCell(i).toInt(nullptr, 16),
                                                8, 2, QChar('0'));
        ui->memoryDisplay->setItem(i, 1, new QTableWidgetItem(binaryValue));

        // Hex column (display the instruction in hex)
        QString hexValue = m_cpu->m_memory->getCell(i).toUpper();
        ui->memoryDisplay->setItem(i, 2, new QTableWidgetItem(hexValue));

        // Integer representation of the instruction
        QString intValue = QString::number(m_cpu->m_memory->getCell(i).toInt(nullptr, 16));
        ui->memoryDisplay->setItem(i, 3, new QTableWidgetItem(intValue));
    }
}

/**
 * @brief Setting Register display section*/
void MainWindow::registerDisplay() {
    ui->registerDisplay->setRowCount(16);
    ui->registerDisplay->setColumnCount(4);
    QStringList r_headers = {"Address", "Binary", "Hex", "Int"};
    ui->registerDisplay->setHorizontalHeaderLabels(r_headers);

    // Setting memory display properties
    ui->registerDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers); // Make table read-only
    ui->registerDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns
    ui->registerDisplay->verticalHeader()->setVisible(false); // Hide row numbers if unnecessary
    ui->registerDisplay->setSelectionMode(QAbstractItemView::NoSelection); // Disable selection
}


void MainWindow::updateRegisterDisplay() {
    for (int i = 0; i < 256; ++i) {
        // Address column (display as hex)
        QString address = QString::number(i, 16).toUpper().rightJustified(2, '0');
        ui->registerDisplay->setItem(i, 0, new QTableWidgetItem(address));

        // Binary column (initialize with 8-bit binary representation)
        QString binaryValue = QString("%1").arg(m_cpu->m_register->getCell(i).toInt(nullptr, 16),
                                                8, 2, QChar('0'));
        ui->registerDisplay->setItem(i, 1, new QTableWidgetItem(binaryValue));

        // Hex column (display the instruction in hex)
        QString hexValue = m_cpu->m_register->getCell(i).toUpper();
        ui->registerDisplay->setItem(i, 2, new QTableWidgetItem(hexValue));

        // Integer representation of the instruction
        QString intValue = QString::number(m_cpu->m_register->getCell(i).toInt(nullptr, 16));
        ui->registerDisplay->setItem(i, 3, new QTableWidgetItem(intValue));
    }
}

void MainWindow::onOpenInstructionFileClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open instruction File"),
                                                    "", tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile instructionsFile(fileName);
        if (instructionsFile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&instructionsFile);
            QString instruction;
            while (!in.atEnd()) {
                in >> instruction;
                QString cell;
                for (int i = 0; i < 2; i++) {
                    cell += instruction[i];
                }
                m_cpu->m_memory->setCell(cpu::m_programCounter++, cell);
                cell = "";
                for (int i = 2; i < 4; i++) {
                    cell += instruction[i];
                }
                m_cpu->m_memory->setCell(cpu::m_programCounter++, cell);
            }
            cpu::m_programCounter = 0;
            instructionsFile.close();
            updateMemoryDisplay();
            QMessageBox::information(this, "File Opened", "Instructions file opened successfully");
        } else {
            QMessageBox::warning(this, "Error", "Could not open the instructionsFile for reading.");
        }
    }
    else {
        QMessageBox::warning(this, "Error", "Could not open the instructionFile");
    }
}


void MainWindow::onFetchButtonClicked()
{
    m_cpu->fetch();
    updateMemoryDisplay();
    ui->instructionDecode->setText(m_cpu->m_instructionRegister);
    ui->pCounter->setText(QString::number(cpu::m_programCounter));
}


void MainWindow::onDecodeButtonClicked()
{
    auto decoded = m_cpu->decode();

    if (decoded.size() != 4) {
        ui->opCodeDisplay->setText(m_cpu->m_instructionRegister[0]);
        ui->rDisplay->setText(m_cpu->m_instructionRegister[1]);
        ui->xDisplay->setText(m_cpu->m_instructionRegister[2]);
        ui->yDisplay->setText(m_cpu->m_instructionRegister[3]);
        ui->encodedInsMessage->setText(decoded);
    }
    else {
        ui->opCodeDisplay->clear();
        ui->rDisplay->clear();
        ui->xDisplay->clear();
        ui->yDisplay->clear();
        ui->encodedInsMessage->setText("Failed to Decode");
    }
    ui->pCounter->setText(QString::number(cpu::m_programCounter));
}


void MainWindow::on_execute_button_clicked()
{
    m_cpu->execute();
    updateMemoryDisplay();
    updateRegisterDisplay();
    ui->pCounter->setText(QString::number(cpu::m_programCounter));
}


void MainWindow::on_resetCounter_clicked()
{
    cpu::m_programCounter = 0;
    ui->pCounter->setText(QString::number(cpu::m_programCounter));
}


void MainWindow::on_pCounter_textChanged(const QString &arg1)
{
    bool ok;
    cpu::m_programCounter = arg1.toInt(&ok);
    ui->pCounter->setText(QString::number(cpu::m_programCounter));
}


void MainWindow::on_instructionDecode_textChanged(const QString &arg1) const
{
    m_cpu->m_instructionRegister = arg1;
}


void MainWindow::on_runOneCycleButton_clicked()
{
    MainWindow::onFetchButtonClicked();
    MainWindow::onDecodeButtonClicked();
    MainWindow::on_execute_button_clicked();
}


void MainWindow::on_clearMemoryButton_clicked()
{
    for (int i = 0; i < 256; i++) {
        m_cpu->m_memory->setCell(i, "00");
    }
    updateMemoryDisplay();
}


void MainWindow::on_clearRegButton_clicked()
{
    for (int i = 0; i < 16; i++) {
        m_cpu->m_register->setCell(i, "00");
    }
    updateRegisterDisplay();
}


void MainWindow::on_memoryDisplay_cellChanged(int row, int column)
{
    if (column == 1) {
        QString newBinaryValue = ui->memoryDisplay->item(row, column)->text();
        QString newHexValue = QString::number(newBinaryValue.toInt(nullptr, 2), 16).toUpper().rightJustified(2, '0');
        m_cpu->m_memory->setCell(row, newHexValue);
        updateMemoryDisplay();
    }

    else if (column == 2) {
        QString newHexValue = ui->memoryDisplay->item(row, column)->text();
        QString newBinaryValue = QString::number(newHexValue.toInt(nullptr, 16), 2).rightJustified(8, '0');
        m_cpu->m_memory->setCell(row, newBinaryValue);
        updateMemoryDisplay();
    }

    else if (column == 3) {
        QString newIntValue = ui->memoryDisplay->item(row, column)->text();
        QString newHexValue = QString::number(newIntValue.toInt(nullptr, 10), 16).toUpper().rightJustified(2, '0');
        m_cpu->m_memory->setCell(row, newHexValue);
        updateMemoryDisplay();
    }
}

