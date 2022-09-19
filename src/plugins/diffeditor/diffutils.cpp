/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/
#include <utils/porting.h>
    return Utils::toSet(leftSelection).unite(Utils::toSet(rightSelection)).size();
    const bool leftLineEqual = !leftLines.isEmpty()
            ? leftLines.last().text.isEmpty()
            : true;
    const bool rightLineEqual = !rightLines.isEmpty()
            ? rightLines.last().text.isEmpty()
            : true;
    QList<TextLineData> leftData = assemblyRows(leftLines,
                                                leftSpans);
    QList<TextLineData> rightData = assemblyRows(rightLines,
                                                 rightSpans);
        chunkData.leftStartingLineNumber = leftLineNumber;
        chunkData.rightStartingLineNumber = rightLineNumber;
            if (rowData.leftLine.textLineType == TextLineData::TextLine)
            if (rowData.rightLine.textLineType == TextLineData::TextLine)
        return QString();
            if (rowData.leftLine.textLineType != TextLineData::Separator
                    || rowData.rightLine.textLineType != TextLineData::TextLine)
            if (rowData.rightLine.textLineType != TextLineData::Separator
                    || rowData.leftLine.textLineType != TextLineData::TextLine)
                                                   rowData.rightLine.text,
            if (rowData.leftLine.textLineType == TextLineData::TextLine)
                leftBuffer.append(rowData.leftLine);
            if (rowData.rightLine.textLineType == TextLineData::TextLine)
                rightBuffer.append(rowData.rightLine);
            + QString::number(chunkData.leftStartingLineNumber + 1)
            + QString::number(chunkData.rightStartingLineNumber + 1)
        str << fileData.leftFileInfo.fileName;
        str << fileData.rightFileInfo.fileName;
            str << "diff --git a/" << fileData.leftFileInfo.fileName
                << " b/" << fileData.rightFileInfo.fileName << '\n';
        str << "index " << fileData.leftFileInfo.typeInfo << ".." << fileData.rightFileInfo.typeInfo;
static QList<RowData> readLines(StringView patch, bool lastChunk, bool *lastChunkAtTheEndOfFile, bool *ok)
    const QVector<StringView> lines = patch.split(newLine);
        StringView line = lines.at(i);
        return QList<RowData>();
static StringView readLine(StringView text, StringView *remainingText, bool *hasNewLine)
            *remainingText = StringView();
static bool detectChunkData(StringView chunkDiff, ChunkData *chunkData, StringView *remainingPatch)
    const StringView chunkLine = readLine(chunkDiff, remainingPatch, &hasNewLine);
    StringView leftPos = chunkLine.mid(leftPosStart, leftPosLength);
    StringView rightPos = chunkLine.mid(rightPosStart, rightPosLength);
    const StringView optionalHint = chunkLine.mid(optionalHintStart, optionalHintLength);
    chunkData->leftStartingLineNumber = leftLineNumber - 1;
    chunkData->rightStartingLineNumber = rightLineNumber - 1;
static QList<ChunkData> readChunks(StringView patch, bool *lastChunkAtTheEndOfFile, bool *ok)
        const StringView chunkDiff = patch.mid(chunkStart, chunkEnd - chunkStart);
        StringView lines;
static FileData readDiffHeaderAndChunks(StringView headerAndChunks, bool *ok)
    StringView patch = headerAndChunks;
        fileData.leftFileInfo.fileName = leftMatch.captured(1);
            fileData.rightFileInfo.fileName = rightMatch.captured(1);
            fileData.leftFileInfo.fileName = binaryMatch.captured(1);
            fileData.rightFileInfo.fileName = binaryMatch.captured(2);
        return FileData();
static QList<FileData> readDiffPatch(StringView patch, bool *ok, QFutureInterfaceBase *jobController)
                return QList<FileData>();
                StringView headerAndChunks = patch.mid(lastPos, pos - lastPos);
            StringView headerAndChunks = patch.mid(lastPos, patch.size() - lastPos - 1);
        return QList<FileData>();
static bool detectIndexAndBinary(StringView patch, FileData *fileData, StringView *remainingPatch)
    StringView afterNextLine;
    const StringView nextLine = readLine(patch, &afterNextLine, &hasNewLine);
        const StringView indices = nextLine.mid(indexHeader.size());
        fileData->leftFileInfo.typeInfo = indices.left(dotsPosition).toString();
        fileData->rightFileInfo.typeInfo = indices.mid(dotsPosition + 2, length).toString();
            ? devNull : QLatin1String("a/") + fileData->leftFileInfo.fileName;
            ? devNull : QLatin1String("b/") + fileData->rightFileInfo.fileName;
        *remainingPatch = StringView();
    StringView afterMinuses;
    const StringView minuses = readLine(*remainingPatch, &afterMinuses, &hasNewLine);
    StringView afterPluses;
    const StringView pluses = readLine(afterMinuses, &afterPluses, &hasNewLine);
static bool extractCommonFileName(StringView fileNames, StringView *fileName)
    const StringView leftFileName = fileNames.mid(2, fileNameSize - 2);
    const StringView rightFileName = fileNames.mid(fileNameSize + 3, fileNameSize - 2);
static bool detectFileData(StringView patch, FileData *fileData, StringView *remainingPatch)
    StringView afterDiffGit;
    const StringView diffGit = readLine(patch, &afterDiffGit, &hasNewLine);
    const StringView fileNames = diffGit.mid(gitHeader.size());
    StringView commonFileName;
        fileData->leftFileInfo.fileName = fileData->rightFileInfo.fileName = commonFileName.toString();
        StringView afterSecondLine;
        const StringView secondLine = readLine(afterDiffGit, &afterSecondLine, &hasNewLine);
            StringView afterThirdLine;
        StringView afterModeOrSimilarity;
        StringView afterSimilarity;
        const StringView secondLine = readLine(afterDiffGit, &afterModeOrSimilarity, &hasNewLine);
        StringView afterCopyRenameFrom;
        const StringView copyRenameFrom = readLine(afterSimilarity, &afterCopyRenameFrom, &hasNewLine);
            fileData->leftFileInfo.fileName = copyRenameFrom.mid(copyFrom.size()).toString();
            fileData->leftFileInfo.fileName = copyRenameFrom.mid(renameFrom.size()).toString();
        StringView afterCopyRenameTo;
        const StringView copyRenameTo = readLine(afterCopyRenameFrom, &afterCopyRenameTo, &hasNewLine);
            fileData->rightFileInfo.fileName = copyRenameTo.mid(copyTo.size()).toString();
            fileData->rightFileInfo.fileName = copyRenameTo.mid(renameTo.size()).toString();
static QList<FileData> readGitPatch(StringView patch, bool *ok, QFutureInterfaceBase *jobController)
        StringView patch;
            return QList<FileData>();
        const StringView fileDiff = patch.mid(diffStart, diffEnd - diffStart);
        StringView remainingFileDiff;
        return QList<FileData>();
                return QList<FileData>();
        return QList<FileData>();
    StringView croppedPatch = make_stringview(patch);