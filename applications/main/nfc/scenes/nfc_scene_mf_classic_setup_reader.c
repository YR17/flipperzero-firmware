#include "../nfc_app_i.h"
#include "../helpers/protocol_support/nfc_protocol_support_gui_common.h"


void nfc_scene_mf_classic_setup_reader_on_enter(void* context) {
   NfcApp* instance = context;

    FuriString* str = furi_string_alloc();
    for(size_t i = NfcDataGeneratorTypeMfClassicMini; i < NfcDataGeneratorTypeNum; i++) {
        furi_string_cat_str(str, nfc_data_generator_get_name(i));
        furi_string_replace_str(str, "Mifare", "MIFARE");

        submenu_add_item(
            instance->submenu,
            furi_string_get_cstr(str),
            i,
            nfc_protocol_support_common_submenu_callback,
            instance);
        furi_string_reset(str);
    }
    furi_string_free(str);

    view_dispatcher_switch_to_view(instance->view_dispatcher, NfcViewMenu);
}

bool nfc_scene_mf_classic_setup_reader_on_event(void* context, SceneManagerEvent event) {
    NfcApp* instance = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeBack) {
        consumed = scene_manager_search_and_switch_to_previous_scene(
                instance->scene_manager, NfcSceneStart);
    }
    else if(event.type == SceneManagerEventTypeCustom) {
            nfc_data_generator_fill_data(event.event, instance->nfc_device);
            scene_manager_next_scene(instance->scene_manager, NfcSceneSetUid);
            consumed = true;
    }

    return consumed;
}

void nfc_scene_mf_classic_setup_reader_on_exit(void* context) {
    NfcApp* instance = context;

    submenu_reset(instance->submenu);
}