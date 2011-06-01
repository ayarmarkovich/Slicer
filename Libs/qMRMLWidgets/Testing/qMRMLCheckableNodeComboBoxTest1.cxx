/*==============================================================================

  Program: 3D Slicer

  Copyright (c) 2010 Kitware Inc.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// QT includes
#include <QApplication>
#include <QTimer>

// qMRML includes
#include "qMRMLCheckableNodeComboBox.h"
#include "qMRMLSceneFactoryWidget.h"

// MRML includes
#include "vtkMRMLScene.h"

// STD includes
#include <stdlib.h>
#include <iostream>

int qMRMLCheckableNodeComboBoxTest1( int argc, char * argv [] )
{
  QApplication app(argc, argv);

  qMRMLCheckableNodeComboBox nodeSelector;

  // Check default state
  bool addEnabled = nodeSelector.addEnabled();
  bool removeEnabled = nodeSelector.removeEnabled();
  bool editEnabled = nodeSelector.editEnabled();
  // Add button should be enabled
  if (addEnabled || removeEnabled || editEnabled)
    {
    std::cerr << __LINE__ << " - Incorrect state" << std::endl
                          << " Expected => Add[0], Remove[0], Edit[0]" << std::endl
                          << " Current => Add[" << addEnabled << "], "
                          << "Remove[" << removeEnabled << "], "
                          << "Edit[" << editEnabled << "]" << std::endl;
    return EXIT_FAILURE;
    }
  nodeSelector.setNodeTypes(QStringList("vtkMRMLViewNode"));

  qMRMLSceneFactoryWidget sceneFactory;
  sceneFactory.generateScene();
  sceneFactory.generateNode("vtkMRMLViewNode");
  sceneFactory.generateNode("vtkMRMLViewNode");

  nodeSelector.setMRMLScene(sceneFactory.mrmlScene());

  sceneFactory.generateNode("vtkMRMLViewNode");
  sceneFactory.generateNode("vtkMRMLViewNode");
  sceneFactory.generateNode("vtkMRMLViewNode");
  
  nodeSelector.show();

  if (argc < 2 || QString(argv[1]) != "-I")
    {
    QTimer::singleShot(200, &app, SLOT(quit()));
    }

  return app.exec();
}
