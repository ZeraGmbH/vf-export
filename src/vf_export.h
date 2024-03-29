#ifndef VF_EXPORT_H
#define VF_EXPORT_H

#include <QObject>
#include <vf-cpp-entity.h>
#include <vf-cpp-compproxy.h>

namespace zPyInt {
class PythonBinding;
}

namespace vfExport {

/**
 * @brief The vf_export class
 *
 * is an vein module useable with zera-modulemanager.
 * This module binds the PythonConverter Moduel and
 * offers its Features to vein.
 *
 * Setup:
 *
 * @code
 * vf_export* obj=new vf_export(<veinId>)
 *
 * QTimer::singleShot(0, [][]{
 *      obj->initOnce()
 * })
 * @endcode
 *
 * If you want to setup multiple modules use a statemachine
 */

class vf_export : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief vf_export creates entity
     * @param parent
     * @param id: the vein entity id
     */
    explicit vf_export(QObject *parent = nullptr, int id=3);
    /**
     * @brief initOnce
     * @return ture on success
     *
     * sets up entity with all components
     */
    bool initOnce();

    /**
     * @brief getVeinEntity
     * @return the actual entity
     *
     * Take the return value and add it to the top EventHandler system
     */
    VfCpp::VfCppEntity *getVeinEntity() const;
    void setVeinEntity(VfCpp::VfCppEntity *value);

private:
    VfCpp::VfCppEntity *m_entity;
    bool m_isInitalized;

    zPyInt::PythonBinding *py;

    /**
     * @brief m_iPath vein component
     * Path to sqlite db
     */
    QString m_inputPath;
    /**
     * @brief m_oPath vein component
     * Path to xml File
     */
    QString m_outputPath;
    /**
     * @brief m_session vein component
     * session to be converted
     */
    QString m_session;
    /**
     * @brief m_engine vein component
     * Conversion engine path
     */
    QString m_engine;
    /**
     * @brief m_filter
     * filter transactions by this word. Transaction must contain filter expression (no regex)
     */
    QString m_filter;
    /**
     * @brief m_parameters
     * stores the engine parameters available using setParameters
     * inside the engine.
     *
     * The parameters are stores in a json object. Its a generic solution
     * to adapt the parameters to the used engine.
     *
     * Please make sure to use ' instead of " in the json param object.
     *
     * {..."p_param" : "{'par1': 'val1', 'par2' : 'val2'}"
     */
    QString m_parameters;

    /**
     * @brief m_status
     * The Module Status,
     * true: good
     * false: bad
     */
    VfCpp::VeinCompProxy<bool> m_status;

signals:


public slots:
    /**
     * @brief RPC_Convert
     * @param p_params
     * @return true on success
     *
     * The RPC which calls the pyhtonSScritp and converts the
     * sql database.
     */
    QVariant RPC_Convert(QVariantMap p_params);

};

}
#endif // VF_EXPORT_H
