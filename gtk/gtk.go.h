#ifndef GO_GTK_H
#define GO_GTK_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <gdk/gdkx.h>
#endif
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

static void _gtk_init(void* argc, void* argv) {
	gtk_init((int*)argc, (char***)argv);
}

static GtkClipboard* _gtk_clipboard_get_for_display(void* display, void* selection) {
	return gtk_clipboard_get_for_display((GdkDisplay*)display, (GdkAtom)selection);
}

static int _gtk_selection_data_get_length(void* selection_data) {
	return (int) gtk_selection_data_get_length((GtkSelectionData*)selection_data);
}

static void* _gtk_selection_data_get_data(void* selection_data) {
	return (char*) gtk_selection_data_get_data((GtkSelectionData*)selection_data);
}

static char* _gtk_selection_data_get_text(void* selection_data) {
	return (char*) gtk_selection_data_get_text((GtkSelectionData*)selection_data);
}

static void _gtk_drag_finish(void *context, gboolean success, gboolean del, guint32 time_) {
	gtk_drag_finish((GdkDragContext*) context, success, del, time_);
}

static GtkWidget* _gtk_message_dialog_new(GtkWidget* parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType buttons, gchar *message) {
	return gtk_message_dialog_new(
			GTK_WINDOW(parent),
			flags,
			type,
			buttons,
			message, NULL);
}

static GtkWidget* _gtk_message_dialog_new_with_markup(GtkWidget* parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType buttons, gchar *message) {
	return gtk_message_dialog_new_with_markup(
			GTK_WINDOW(parent),
			flags,
			type,
			buttons,
			message, NULL);
}

static GtkWidget* _gtk_file_chooser_dialog_new(const gchar* title,
		GtkWidget* parent, int file_chooser_action, int action, const gchar* button) {
	return gtk_file_chooser_dialog_new(
			title,
			GTK_WINDOW(parent),
			file_chooser_action,
			button,
			action,
			NULL);
}

static GtkWidget* _gtk_file_chooser_widget_new(int file_chooser_action) {
	return gtk_file_chooser_widget_new(file_chooser_action);
}

static GtkTreePath* _gtk_tree_model_get_path(GtkTreeModel* tree_model, GtkTreeIter* iter) {
	return gtk_tree_model_get_path(tree_model, iter);
}

static void _gtk_text_buffer_insert_with_tag(GtkTextBuffer* buffer, GtkTextIter* iter, const gchar* text, gint len, GtkTextTag* tag) {
	gtk_text_buffer_insert_with_tags(buffer, iter, text, len, tag, NULL);
}

//static void _gtk_text_buffer_insert_with_tags_by_name(GtkTextBuffer* buffer, GtkTextIter* iter, const gchar* text, gint len, const gchar* first_tag_name, ...);

static GtkTextTag* _gtk_text_buffer_create_tag(GtkTextBuffer* buffer, const gchar* tag_name) {
	return gtk_text_buffer_create_tag(buffer, tag_name, NULL);
}

static void _gtk_widget_hide_on_delete(GtkWidget* w) {
	g_signal_connect(GTK_WIDGET(w), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

static void _gtk_text_iter_assign(GtkTextIter* one, GtkTextIter* two) {
	*one = *two;
}

static void _apply_property(void* obj, const gchar* prop, const gchar* val) {
	GParamSpec *pspec;
	GValue fromvalue = { 0, };
	GValue tovalue = { 0, };
	pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(obj), prop);
	if (!pspec) return;
	g_value_init(&fromvalue, G_TYPE_STRING);
	g_value_set_string(&fromvalue, val);
	g_value_init(&tovalue, G_PARAM_SPEC_VALUE_TYPE(pspec));
	g_value_transform(&fromvalue, &tovalue);
	g_object_set_property((GObject *)obj, prop, &tovalue);
	g_value_unset(&fromvalue);
	g_value_unset(&tovalue);
}

static GtkTreeViewColumn* _gtk_tree_view_column_new_with_attribute(gchar* title, GtkCellRenderer* cell) {
	return gtk_tree_view_column_new_with_attributes(title, cell, NULL);
}

static GtkTreeViewColumn* _gtk_tree_view_column_new_with_attributes(gchar* title, GtkCellRenderer* cell, gchar* prop, gint column) {
	return gtk_tree_view_column_new_with_attributes(title, cell, prop, column, NULL);
}

static void _gtk_list_store_set_ptr(GtkListStore* list_store, GtkTreeIter* iter, gint column, void* data) {
	gtk_list_store_set(list_store, iter, column, data, -1);
}

static void _gtk_list_store_set_addr(GtkListStore* list_store, GtkTreeIter* iter, gint column, void* data) {
	gtk_list_store_set(list_store, iter, column, *(gpointer*)data, -1);
}

static void _gtk_tree_store_set_ptr(GtkTreeStore* tree_store, GtkTreeIter* iter, gint column, void* data) {
	gtk_tree_store_set(tree_store, iter, column, data, -1);
}

static void _gtk_tree_store_set_addr(GtkTreeStore* tree_store, GtkTreeIter* iter, gint column, void* data) {
	gtk_tree_store_set(tree_store, iter, column, *(gpointer*)data, -1);
}

//static void _gtk_range_get_value(GtkRange* range, gdouble* value) {
//	*value = gtk_range_get_value(range);
//}

typedef struct {
	GtkMenu *menu;
	gint x;
	gint y;
	gboolean push_in;
	gpointer data;
} _gtk_menu_position_func_info;

extern void _go_gtk_menu_position_func(_gtk_menu_position_func_info* gmpfi);
static void _c_gtk_menu_position_func(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer user_data) {
	_gtk_menu_position_func_info gmpfi;
	gmpfi.menu = menu;
	gmpfi.x = *x;
	gmpfi.y = *y;
	gmpfi.push_in = *push_in;
	gmpfi.data = user_data;
	_go_gtk_menu_position_func(&gmpfi);
	*x = gmpfi.x;
	*y = gmpfi.y;
	*push_in = gmpfi.push_in;
#ifdef _WIN32
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	gint h = GTK_WIDGET(menu)->requisition.height;
	if (*y + h > rect.bottom) *y -= h;
#endif
}

static void _gtk_menu_popup(GtkWidget *menu, GtkWidget *parent_menu_shell, GtkWidget *parent_menu_item, void* data, guint button, guint32 activate_time) {
	gtk_menu_popup(GTK_MENU(menu), parent_menu_shell, parent_menu_item, _c_gtk_menu_position_func, (gpointer) data, button, activate_time);
}

static inline GType* make_gtypes(int count) {
	return g_new0(GType, count);
}

static inline void destroy_gtypes(GType* types) {
	g_free(types);
}

static inline void set_gtype(GType* types, int n, int type) {
	types[n] = (GType) type;
}

static inline gchar** make_strings(int count) {
	return (gchar**)malloc(sizeof(gchar*) * count);
}

static inline void destroy_strings(gchar** strings) {
	free(strings);
}

static inline gchar* get_string(gchar** strings, int n) {
	return strings[n];
}

static inline void set_string(gchar** strings, int n, gchar* str) {
	strings[n] = str;
}

static GSList* to_gslist(void* gs) {
	return (GSList*)gs;
}

static int _check_version(int major, int minor, int micro) {
	return GTK_CHECK_VERSION(major, minor, micro);
}

static void _gtk_tree_iter_assign(void* iter, void* to) {
	*(GtkTreeIter*)iter = *(GtkTreeIter*)to;
}

static GtkWidget* _gtk_dialog_get_vbox(GtkWidget* w) {
  return GTK_DIALOG(w)->vbox;
}

//////////////////////////////////////////////
// ############# Version Control #############
//////////////////////////////////////////////

#if GTK_CHECK_VERSION(2,14,0)
static gdouble _gtk_adjustment_get_lower(GtkAdjustment* adjustment) {
	return gtk_adjustment_get_lower(adjustment);
}
static void _gtk_adjustment_set_lower(GtkAdjustment* adjustment, gdouble lower) {
	gtk_adjustment_set_lower(adjustment, lower);
}
static gdouble _gtk_adjustment_get_upper(GtkAdjustment* adjustment) {
	return gtk_adjustment_get_upper(adjustment);
}
static void _gtk_adjustment_set_upper(GtkAdjustment* adjustment, gdouble upper) {
	gtk_adjustment_set_upper(adjustment, upper);
}
static gdouble _gtk_adjustment_get_step_increment(GtkAdjustment* adjustment) {
	return gtk_adjustment_get_step_increment(adjustment);
}
static void _gtk_adjustment_set_step_increment(GtkAdjustment* adjustment, gdouble step_increment) {
	gtk_adjustment_set_step_increment(adjustment, step_increment);
}
static gdouble _gtk_adjustment_get_page_increment(GtkAdjustment* adjustment) {
	return gtk_adjustment_get_page_increment(adjustment);
}
static void _gtk_adjustment_set_page_increment(GtkAdjustment* adjustment, gdouble page_increment) {
	gtk_adjustment_set_page_increment(adjustment, page_increment);
}
static gdouble _gtk_adjustment_get_page_size(GtkAdjustment* adjustment) {
	return gtk_adjustment_get_page_size(adjustment);
}
static void _gtk_adjustment_set_page_size(GtkAdjustment* adjustment, gdouble page_size) {
	gtk_adjustment_set_page_size(adjustment, page_size);
}
static void _gtk_adjustment_configure(GtkAdjustment* adjustment, gdouble value, gdouble lower, gdouble upper, gdouble step_increment, gdouble page_increment, gdouble page_size) {
	gtk_adjustment_configure(adjustment, value, lower, upper, step_increment, page_increment, page_size);
}
#else //GTK_CHECK_VERSION(2,14,0)
static gdouble _gtk_adjustment_get_lower(GtkAdjustment* adjustment) {
	return 0f;
}
static void _gtk_adjustment_set_lower(GtkAdjustment* adjustment, gdouble lower) {
}
static gdouble _gtk_adjustment_get_upper(GtkAdjustment* adjustment) {
	return 0f;
}
static void _gtk_adjustment_set_upper(GtkAdjustment* adjustment, gdouble upper) {
}
static gdouble _gtk_adjustment_get_step_increment(GtkAdjustment* adjustment) {
	return 0f;
}
static void _gtk_adjustment_set_step_increment(GtkAdjustment* adjustment, gdouble step_increment) {
}
static gdouble _gtk_adjustment_get_page_increment(GtkAdjustment* adjustment) {
	return 0f;
}
static void _gtk_adjustment_set_page_increment(GtkAdjustment* adjustment, gdouble page_increment) {
}
static gdouble _gtk_adjustment_get_page_size(GtkAdjustment* adjustment) {
	return 0f;
}
static void _gtk_adjustment_set_page_size(GtkAdjustment* adjustment, gdouble page_size) {
}
static void _gtk_adjustment_configure(GtkAdjustment* adjustment, gdouble value, gdouble lower, gdouble upper, gdouble step_increment, gdouble page_increment, gdouble page_size) {
}
#endif //GTK_CHECK_VERSION(2,14,0)

#if GTK_CHECK_VERSION(2,18,0)
static gboolean _gtk_cell_renderer_toggle_get_activatable(GtkCellRendererToggle *toggle) {
	return gtk_cell_renderer_toggle_get_activatable(toggle);
}
static void _gtk_cell_renderer_toggle_set_activatable(GtkCellRendererToggle *toggle, gboolean setting) {
	gtk_cell_renderer_toggle_set_activatable(toggle, setting);
}
static void _gtk_menu_set_reserve_toggle_size(GtkMenu *menu, gboolean reserve_toggle_size) {
	gtk_menu_set_reserve_toggle_size(menu, reserve_toggle_size);
}
static gboolean _gtk_menu_get_reserve_toggle_size(GtkMenu *menu) {
	return gtk_menu_get_reserve_toggle_size(menu);
}
static gboolean _gtk_range_get_flippable(GtkRange *range) {
	return gtk_range_get_flippable(range);
}
static void _gtk_range_set_flippable(GtkRange *range, gboolean flippable) {
	gtk_range_set_flippable(range, flippable);
}
static void _gtk_widget_get_allocation(GtkWidget *widget, GtkAllocation *allocation) {
	gtk_widget_get_allocation(widget, allocation);
}
static void _gtk_widget_set_allocation(GtkWidget *widget, const GtkAllocation *allocation) {
	gtk_widget_set_allocation(widget, allocation);
}
static gboolean _gtk_widget_get_app_paintable(GtkWidget *widget) {
	return gtk_widget_get_app_paintable(widget);
}
static gboolean _gtk_widget_get_can_default(GtkWidget *widget) {
	return gtk_widget_get_can_default(widget);
}
static void _gtk_widget_set_can_default(GtkWidget *widget, gboolean can_default) {
	gtk_widget_set_can_default(widget, can_default);
}
static gboolean _gtk_widget_get_can_focus(GtkWidget *widget) {
	return gtk_widget_get_can_focus(widget);
}
static void _gtk_widget_set_can_focus(GtkWidget *widget, gboolean can_focus) {
	gtk_widget_set_can_focus(widget, can_focus);
}
static gboolean _gtk_widget_get_double_buffered(GtkWidget *widget) {
	return gtk_widget_get_double_buffered(widget);
}
static gboolean _gtk_widget_get_has_window(GtkWidget *widget) {
	return gtk_widget_get_has_window(widget);
}
static void _gtk_widget_set_has_window(GtkWidget *widget, gboolean has_window) {
	gtk_widget_set_has_window(widget, has_window);
}
static gboolean _gtk_widget_get_sensitive(GtkWidget *widget) {
	return gtk_widget_get_sensitive(widget);
}
static gboolean _gtk_widget_is_sensitive(GtkWidget *widget) {
	return gtk_widget_is_sensitive(widget);
}
static GtkStateType _gtk_widget_get_state(GtkWidget *widget) {
	return gtk_widget_get_state(widget);
}
static gboolean _gtk_widget_get_visible(GtkWidget *widget) {
	return gtk_widget_get_visible(widget);
}
static void _gtk_widget_set_visible(GtkWidget *widget, gboolean visible) {
	gtk_widget_set_visible(widget, visible);
}
static gboolean _gtk_widget_has_default(GtkWidget *widget) {
	return gtk_widget_has_default(widget);
}
static gboolean _gtk_widget_has_focus(GtkWidget *widget) {
	return gtk_widget_has_focus(widget);
}
static gboolean _gtk_widget_has_grab(GtkWidget *widget) {
	return gtk_widget_has_grab(widget);
}
static gboolean _gtk_widget_is_drawable(GtkWidget *widget) {
	return gtk_widget_is_drawable(widget);
}
static gboolean _gtk_widget_is_toplevel(GtkWidget *widget) {
	return gtk_widget_is_toplevel(widget);
}
static void _gtk_widget_set_window(GtkWidget *widget, GdkWindow *window) {
	gtk_widget_set_window(widget, window);
}
static void _gtk_widget_set_receives_default(GtkWidget *widget, gboolean receives_default) {
	gtk_widget_set_receives_default(widget, receives_default);
}
static gboolean _gtk_widget_get_receives_default(GtkWidget *widget) {
	return gtk_widget_get_receives_default(widget);
}
static GtkWidget* _gtk_info_bar_new() {
	return gtk_info_bar_new();
}
static void _gtk_info_bar_add_action_widget(GtkInfoBar *info_bar, GtkWidget *child, gint response_id) {
	gtk_info_bar_add_action_widget(info_bar, child, response_id);
}
static GtkWidget* _gtk_info_bar_add_button(GtkInfoBar *info_bar, const gchar *button_text, gint response_id) {
	return gtk_info_bar_add_button(info_bar, button_text, response_id);
}
static void _gtk_info_bar_set_response_sensitive(GtkInfoBar *info_bar, gint response_id, gboolean setting) {
	gtk_info_bar_set_response_sensitive(info_bar, response_id, setting);
}
static void _gtk_info_bar_set_default_response(GtkInfoBar *info_bar, gint response_id) {
	gtk_info_bar_set_default_response(info_bar, response_id);
}
static void _gtk_info_bar_response(GtkInfoBar *info_bar, gint response_id) {
	gtk_info_bar_response(info_bar, response_id);
}
static void _gtk_info_bar_set_message_type(GtkInfoBar *info_bar, GtkMessageType message_type) {
	gtk_info_bar_set_message_type(info_bar, message_type);
}
static GtkMessageType _gtk_info_bar_get_message_type(GtkInfoBar *info_bar) {
	return gtk_info_bar_get_message_type(info_bar);
}
static GtkWidget* _gtk_info_bar_get_action_area(GtkInfoBar *info_bar) {
	return gtk_info_bar_get_action_area(info_bar);
}
static GtkWidget* _gtk_info_bar_get_content_area(GtkInfoBar *info_bar) {
	return gtk_info_bar_get_content_area(info_bar);
}
static GtkWidget* _gtk_entry_new_with_buffer(GtkEntryBuffer *buffer) {
	return gtk_entry_new_with_buffer(buffer);
}
static GtkEntryBuffer* _gtk_entry_get_buffer(GtkEntry *entry) {
	return gtk_entry_get_buffer(entry);
}
static void _gtk_entry_set_buffer(GtkEntry *entry,  GtkEntryBuffer *buffer) {
	gtk_entry_set_buffer(entry, buffer);
}
static GtkEntryBuffer* _gtk_entry_buffer_new(const gchar *initial_chars, gint n_initial_chars) {
	return gtk_entry_buffer_new(initial_chars, n_initial_chars);
}
static const gchar* _gtk_entry_buffer_get_text(GtkEntryBuffer *buffer) {
	return gtk_entry_buffer_get_text(buffer);
}
static void _gtk_entry_buffer_set_text(GtkEntryBuffer *buffer, const gchar *chars, gint n_chars) {
	gtk_entry_buffer_set_text(buffer, chars, n_chars);
}
//static gsize _gtk_entry_buffer_get_bytes(GtkEntryBuffer *buffer) {
//	return gtk_entry_buffer_get_bytes(buffer);
//}
static guint _gtk_entry_buffer_get_length(GtkEntryBuffer *buffer) {
	return gtk_entry_buffer_get_length(buffer);
}
static gint _gtk_entry_buffer_get_max_length(GtkEntryBuffer *buffer) {
	return gtk_entry_buffer_get_max_length(buffer);
}
static void _gtk_entry_buffer_set_max_length(GtkEntryBuffer *buffer, gint max_length) {
	gtk_entry_buffer_set_max_length(buffer, max_length);
}
static guint _gtk_entry_buffer_insert_text(GtkEntryBuffer *buffer, guint position, const gchar *chars, gint n_chars) {
	return gtk_entry_buffer_insert_text(buffer, position, chars, n_chars);
}
static guint _gtk_entry_buffer_delete_text(GtkEntryBuffer *buffer, guint position, gint n_chars) {
	return gtk_entry_buffer_delete_text(buffer, position, n_chars);
}
static void _gtk_status_icon_set_title(GtkStatusIcon *status_icon, const gchar *title) {
	gtk_status_icon_set_title(status_icon, title);
}
static const gchar* _gtk_status_icon_get_title(GtkStatusIcon *status_icon) {
	return gtk_status_icon_get_title(status_icon);
}
#else //!GTK_CHECK_VERSION(2,18,0)
static gboolean _gtk_cell_renderer_toggle_get_activatable(GtkCellRendererToggle *toggle) {
	return 0;
}
static void _gtk_cell_renderer_toggle_set_activatable(GtkCellRendererToggle *toggle, gboolean setting) {
}
static void _gtk_menu_set_reserve_toggle_size(GtkMenu *menu, gboolean reserve_toggle_size) {
}
static gboolean _gtk_menu_get_reserve_toggle_size(GtkMenu *menu) {
	return 0;
}
static gboolean _gtk_range_get_flippable(GtkRange *range) {
	return 0;
}
static void _gtk_range_set_flippable(GtkRange *range, gboolean flippable) {
}
static void _gtk_widget_get_allocation(GtkWidget *widget, GtkAllocation *allocation) {
}
static void _gtk_widget_set_allocation(GtkWidget *widget, const GtkAllocation *allocation) {
}
static gboolean _gtk_widget_get_app_paintable(GtkWidget *widget) {
	return 0;
}
static gboolean _gtk_widget_get_can_default(GtkWidget *widget) {
	return 0;
}
static void _gtk_widget_set_can_default(GtkWidget *widget, gboolean can_default) {
}
static gboolean _gtk_widget_get_can_focus(GtkWidget *widget) {
	return 0;
}
static void _gtk_widget_set_can_focus(GtkWidget *widget, gboolean can_focus) {
}
static gboolean _gtk_widget_get_double_buffered(GtkWidget *widget) {
	return 0;
}
static gboolean _gtk_widget_get_has_window(GtkWidget *widget) {
	return 0;
}
static void _gtk_widget_set_has_window(GtkWidget *widget, gboolean has_window) {
}
static gboolean _gtk_widget_get_sensitive(GtkWidget *widget) {
	return 0;
}
static gboolean _gtk_widget_is_sensitive(GtkWidget *widget) {
	return 0;
}
static GtkStateType _gtk_widget_get_state(GtkWidget *widget) {
	return 0;
}
static gboolean _gtk_widget_get_visible(GtkWidget *widget) {
	return 0;
}
static void _gtk_widget_set_visible(GtkWidget *widget, gboolean visible) {
}
static gboolean _gtk_widget_has_default(GtkWidget *widget) {
	return 0;
}
static gboolean _gtk_widget_has_focus(GtkWidget *widget) {
	return 0:
}
static gboolean _gtk_widget_has_grab(GtkWidget *widget) {
	return 0;
}
static gboolean _gtk_widget_is_drawable(GtkWidget *widget) {
	return 0:
}
static gboolean _gtk_widget_is_toplevel(GtkWidget *widget) {
	return 0;
}
static void _gtk_widget_set_window(GtkWidget *widget, GdkWindow *window) {
}
static void _gtk_widget_set_receives_default(GtkWidget *widget, gboolean receives_default) {
}
static gboolean _gtk_widget_get_receives_default(GtkWidget *widget) {
	return 0;
}
static GtkWidget* _gtk_info_bar_new() {
	return NULL;
}
static void _gtk_info_bar_add_action_widget(GtkInfoBar *info_bar, GtkWidget *child, gint response_id) {
}
static GtkWidget* _gtk_info_bar_add_button(GtkInfoBar *info_bar, const gchar *button_text, gint response_id) {
	return NULL;
}
static void _gtk_info_bar_set_response_sensitive(GtkInfoBar *info_bar, gint response_id, gboolean setting) {
}
static void _gtk_info_bar_set_default_response(GtkInfoBar *info_bar, gint response_id) {
}
static void _gtk_info_bar_response(GtkInfoBar *info_bar, gint response_id) {
}
static void _gtk_info_bar_set_message_type(GtkInfoBar *info_bar, GtkMessageType message_type) {
}
static GtkMessageType _gtk_info_bar_get_message_type(GtkInfoBar *info_bar) {
	return 0;
}
static GtkWidget* _gtk_info_bar_get_action_area(GtkInfoBar *info_bar) {
	return NULL;
}
static GtkWidget* _gtk_info_bar_get_content_area(GtkInfoBar *info_bar) {
	return NULL;
}
static GtkWidget* _gtk_entry_new_with_buffer(GtkEntryBuffer *buffer) {
	return NULL;
}
static GtkEntryBuffer* _gtk_entry_get_buffer(GtkEntry *entry) {
	return NULL;
}
static void _gtk_entry_set_buffer(GtkEntry *entry,  GtkEntryBuffer *buffer) {
}
static GtkEntryBuffer* _gtk_entry_buffer_new(const gchar *initial_chars, gint n_initial_chars) {
	return NULL;
}
static const gchar* _gtk_entry_buffer_get_text(GtkEntryBuffer *buffer) {
	return NULL;
}
static void _gtk_entry_buffer_set_text(GtkEntryBuffer *buffer, const gchar *chars, gint n_chars) {
}
//static gsize _gtk_entry_buffer_get_bytes(GtkEntryBuffer *buffer) {
//	return 0;
//}
static guint _gtk_entry_buffer_get_length(GtkEntryBuffer *buffer) {
	return 0;
}
static gint _gtk_entry_buffer_get_max_length(GtkEntryBuffer *buffer) {
	return 0;
}
static void _gtk_entry_buffer_set_max_length(GtkEntryBuffer *buffer, gint max_length) {
}
static guint _gtk_entry_buffer_insert_text(GtkEntryBuffer *buffer, guint position, const gchar *chars, gint n_chars) {
	return 0;
}
static guint _gtk_entry_buffer_delete_text(GtkEntryBuffer *buffer, guint position, gint n_chars) {
	return 0;
}
static void _gtk_status_icon_set_title(GtkStatusIcon *status_icon, const gchar *title) {
}
static const gchar* _gtk_status_icon_get_title(GtkStatusIcon *status_icon) {
	return NULL;
}
#endif //GTK_CHECK_VERSION(2,18,0)

#if GTK_CHECK_VERSION(2,20,0)
static GtkWidget* _gtk_dialog_get_widget_for_response(GtkDialog* dialog, gint id) {
	return gtk_dialog_get_widget_for_response(dialog, id);
}
static GdkWindow* _gtk_viewport_get_bin_window(GtkViewport *viewport) {
	return gtk_viewport_get_bin_window(viewport);
}
static void _gtk_status_icon_set_name(GtkStatusIcon *status_icon, const gchar *name) {
	gtk_status_icon_set_name(status_icon, name);
}
#else //GTK_CHECK_VERSION(2,20,0)
static GtkWidget* _gtk_dialog_get_widget_for_response(GtkDialog* dialog, gint id) {
	return NULL;
}
static GdkWindow* _gtk_viewport_get_bin_window(GtkViewport *viewport) {
	return NULL;
}
static void _gtk_status_icon_set_name(GtkStatusIcon *status_icon, const gchar *name) {
}
#endif //GTK_CHECK_VERSION(2,20,0)

#if GTK_CHECK_VERSION(2,22,0)
static GtkWidget* _gtk_accessible_get_widget(GtkAccessible *accessible) {
	return gtk_accessible_get_widget(accessible);
}
static void _gtk_accessible_set_widget(GtkAccessible *accessible, GtkWidget *widget) {
	gtk_accessible_set_widget(accessible, widget);
}
static GdkWindow* _gtk_viewport_get_view_window(GtkViewport *viewport) {
	return gtk_viewport_get_view_window(viewport);
}
#else //GTK_CHECK_VERSION(2,22,0)
static GtkWidget* _gtk_accessible_get_widget(GtkAccessible *accessible) {
	return NULL;
}
static void _gtk_accessible_set_widget(GtkAccessible *accessible, GtkWidget *widget) {
}
static GdkWindow* _gtk_viewport_get_view_window(GtkViewport *viewport) {
	return NULL;
}
#endif //GTK_CHECK_VERSION(2,22,0)

#if GTK_CHECK_VERSION(2,24,0)
static GtkWidget* _gtk_combo_box_new_with_entry(void) {
	return gtk_combo_box_new_with_entry();
}
static GtkWidget* _gtk_combo_box_new_with_model_and_entry(GtkTreeModel *model) {
	return gtk_combo_box_new_with_model_and_entry(model);
}
static GtkWidget* _gtk_combo_box_text_new(void) {
	return gtk_combo_box_text_new();
}
static GtkWidget* _gtk_combo_box_text_new_with_entry(void) {
	return gtk_combo_box_text_new_with_entry();
}
static void _gtk_combo_box_text_append_text(GtkComboBoxText *combo_box, const gchar *text) {
	gtk_combo_box_text_append_text(combo_box, text);
}
static void  _gtk_combo_box_text_insert_text(GtkComboBoxText *combo_box, gint position, const gchar *text) {
	gtk_combo_box_text_insert_text(combo_box, position, text);
}
static void _gtk_combo_box_text_prepend_text(GtkComboBoxText *combo_box, const gchar *text) {
	gtk_combo_box_text_prepend_text(combo_box, text);
}
static void _gtk_combo_box_text_remove(GtkComboBoxText *combo_box, gint position) {
	gtk_combo_box_text_remove(combo_box, position);
}
static gchar* _gtk_combo_box_text_get_active_text(GtkComboBoxText *combo_box) {
	return gtk_combo_box_text_get_active_text(combo_box);
}
static void _gtk_notebook_set_group_name(GtkNotebook* notebook, const gchar* group_name) {
	gtk_notebook_set_group_name(notebook, group_name);
}
static const gchar* _gtk_notebook_get_group_name(GtkNotebook* notebook) {
	return gtk_notebook_get_group_name(notebook);
}
#else //GTK_CHECK_VERSION(2,24,0)
static GtkWidget* _gtk_combo_box_new_with_entry(void) {
	return NULL;
}
static GtkWidget* _gtk_combo_box_new_with_model_and_entry(GtkTreeModel *model) {
	return NULL;
}
static GtkWidget* _gtk_combo_box_text_new(void) {
	return NULL;
}
static GtkWidget* _gtk_combo_box_text_new_with_entry(void) {
	return NULL;
}
static void _gtk_combo_box_text_append_text(GtkWidget *combo_box, const gchar *text) {
}
static void  _gtk_combo_box_text_insert_text(GtkWidget *combo_box, gint position, const gchar *text) {
}
static void _gtk_combo_box_text_prepend_text(GtkWidget *combo_box, const gchar *text) {
}
static void _gtk_combo_box_text_remove(GtkWidget *combo_box, gint position) {
}
static gchar* _gtk_combo_box_text_get_active_text(GtkWidget *combo_box) {
	return NULL;
}
static void _gtk_notebook_set_group_name(GtkNotebook* notebook, const gchar* group_name) {
}
static const gchar* _gtk_notebook_get_group_name(GtkNotebook* notebook) {
	return NULL;
}
#endif //GTK_CHECK_VERSION(2,24,0)

static GtkCellRenderer* _gtk_cell_renderer_spinner_new(void) {
#ifdef GTK_CELL_RENDERER_SPINNER //2.20
	return gtk_cell_renderer_spinner_new();
#else
	return gtk_cell_renderer_spin_new();
#endif
}

//////////////////////////////////////////////
// ################# Casting #################
//////////////////////////////////////////////

static inline GObject* to_GObject(void* o) { return G_OBJECT(o); }
static inline gchar* to_gcharptr(const char* s) { return (gchar*)s; }
static inline char* to_charptr(const gchar* s) { return (char*)s; }
static inline char* to_charptr_guchar(const guchar* s) { return (char*)s; }
static inline char* to_charptr_voidp(const void* s) { return (char*)s; }
static inline gchar** next_gcharptr(gchar** s) { return (s+1); }
static inline void free_string(char* s) { free(s); }

static GValue* to_GValueptr(void* s) { return (GValue*)s; }
static GtkWindow* to_GtkWindow(GtkWidget* w) { return GTK_WINDOW(w); }
static GtkDialog* to_GtkDialog(GtkWidget* w) { return GTK_DIALOG(w); }
static GtkAboutDialog* to_GtkAboutDialog(GtkWidget* w) { return GTK_ABOUT_DIALOG(w); }
static GtkContainer* to_GtkContainer(GtkWidget* w) { return GTK_CONTAINER(w); }
static GtkFileChooser* to_GtkFileChooser(GtkWidget* w) { return GTK_FILE_CHOOSER(w); }
static GtkFontSelectionDialog* to_GtkFontSelectionDialog(GtkWidget* w) { return GTK_FONT_SELECTION_DIALOG(w); }
static GtkLabel* to_GtkLabel(GtkWidget* w) { return GTK_LABEL(w); }
static GtkButton* to_GtkButton(GtkWidget* w) { return GTK_BUTTON(w); }
static GtkSpinButton* to_GtkSpinButton(GtkWidget* w) { return GTK_SPIN_BUTTON(w); }
static GtkRadioButton* to_GtkRadioButton(GtkWidget* w) { return GTK_RADIO_BUTTON(w); }
static GtkFontButton* to_GtkFontButton(GtkWidget* w) { return GTK_FONT_BUTTON(w); }
static GtkLinkButton* to_GtkLinkButton(GtkWidget* w) { return GTK_LINK_BUTTON(w); }
static GtkComboBox* to_GtkComboBox(GtkWidget* w) { return GTK_COMBO_BOX(w); }
static GtkComboBoxEntry* to_GtkComboBoxEntry(GtkWidget* w) { return GTK_COMBO_BOX_ENTRY(w); }
static GtkMessageDialog* to_GtkMessageDialog(GtkWidget* w) { return GTK_MESSAGE_DIALOG(w); }

#if GTK_CHECK_VERSION(2,24,0)
static GtkComboBoxText* to_GtkComboBoxText(GtkWidget* w) { return GTK_COMBO_BOX_TEXT(w); }
#else
static GtkWidget* to_GtkComboBoxText(GtkWidget* w) { return w; }
#endif

static GtkAccessible* to_GtkAccessible(void* w) { return GTK_ACCESSIBLE(w); }
static GtkBin* to_GtkBin(GtkWidget* w) { return GTK_BIN(w); }
static GtkStatusbar* to_GtkStatusbar(GtkWidget* w) { return GTK_STATUSBAR(w); }
static GtkInfoBar* to_GtkInfoBar(GtkWidget* w) { return GTK_INFO_BAR(w); }
static GtkFrame* to_GtkFrame(GtkWidget* w) { return GTK_FRAME(w); }
static GtkBox* to_GtkBox(GtkWidget* w) { return GTK_BOX(w); }
static GtkPaned* to_GtkPaned(GtkWidget* w) { return GTK_PANED(w); }
static GtkToggleButton* to_GtkToggleButton(GtkWidget* w) { return GTK_TOGGLE_BUTTON(w); }
static GtkAccelLabel* to_GtkAccelLabel(GtkWidget* w) { return GTK_ACCEL_LABEL(w); }
static GtkEntry* to_GtkEntry(GtkWidget* w) { return GTK_ENTRY(w); }
static GtkAdjustment* to_GtkAdjustment(GtkObject* o) { return GTK_ADJUSTMENT(o); }
static GtkTextView* to_GtkTextView(GtkWidget* w) { return GTK_TEXT_VIEW(w); }
static GtkTextBuffer* to_GtkTextBuffer(void* w) { return GTK_TEXT_BUFFER(w); }
static GtkMenu* to_GtkMenu(GtkWidget* w) { return GTK_MENU(w); }
static GtkMenuBar* to_GtkMenuBar(GtkWidget* w) { return GTK_MENU_BAR(w); }
static GtkMenuShell* to_GtkMenuShell(GtkWidget* w) { return GTK_MENU_SHELL(w); }
static GtkMenuItem* to_GtkMenuItem(GtkWidget* w) { return GTK_MENU_ITEM(w); }
static GtkItem* to_GtkItem(GtkWidget* w) { return GTK_ITEM(w); }
static GtkToolbar* to_GtkToolbar(GtkWidget* w) { return GTK_TOOLBAR(w); }
static GtkToolItem* to_GtkToolItem(GtkWidget* w) { return GTK_TOOL_ITEM(w); }
static GtkSeparatorToolItem* to_GtkSeparatorToolItem(GtkWidget* w) { return GTK_SEPARATOR_TOOL_ITEM(w); }
static GtkToolButton* to_GtkToolButton(GtkWidget* w) { return GTK_TOOL_BUTTON(w); }
static GtkToggleToolButton* to_GtkToggleToolButton(GtkWidget* w) { return GTK_TOGGLE_TOOL_BUTTON(w); }
static GtkScrolledWindow* to_GtkScrolledWindow(GtkWidget* w) { return GTK_SCROLLED_WINDOW(w); }
static GtkViewport* to_GtkViewport(GtkWidget* w) { return GTK_VIEWPORT(w); }
static GtkWidget* to_GtkWidget(void* w) { return GTK_WIDGET(w); }
static GdkWindow* to_GdkWindow(void* w) { return GDK_WINDOW(w); }
static GtkTreeView* to_GtkTreeView(GtkWidget* w) { return GTK_TREE_VIEW(w); }
static GtkIconView* to_GtkIconView(GtkWidget* w) { return GTK_ICON_VIEW(w); }
static GtkEditable* to_GtkEditable(GtkWidget* w) { return GTK_EDITABLE(w); }
static GtkCellRendererText* to_GtkCellRendererText(GtkCellRenderer* w) { return GTK_CELL_RENDERER_TEXT(w); }
static GtkCellRendererToggle* to_GtkCellRendererToggle(GtkCellRenderer* w) { return GTK_CELL_RENDERER_TOGGLE(w); }
static GtkScale* to_GtkScale(GtkWidget* w) { return GTK_SCALE(w); }
static GtkRange* to_GtkRange(GtkWidget* w) { return GTK_RANGE(w); }
static GtkTreeModel* to_GtkTreeModelFromListStore(GtkListStore* w) { return GTK_TREE_MODEL(w); }
static GtkTreeModel* to_GtkTreeModelFromTreeStore(GtkTreeStore* w) { return GTK_TREE_MODEL(w); }
static GtkImage* to_GtkImage(GtkWidget* w) { return GTK_IMAGE(w); }
static GtkNotebook* to_GtkNotebook(GtkWidget* w) { return GTK_NOTEBOOK(w); }
static GtkTable* to_GtkTable(GtkWidget* w) { return GTK_TABLE(w); }
static GtkDrawingArea* to_GtkDrawingArea(GtkWidget* w) { return GTK_DRAWING_AREA(w); }
static GtkAssistant* to_GtkAssistant(GtkWidget* w) { return GTK_ASSISTANT(w); }
static GtkExpander* to_GtkExpander(GtkWidget* w) { return GTK_EXPANDER(w); }
static GtkAlignment* to_GtkAlignment(GtkWidget* w) { return GTK_ALIGNMENT(w); }
static GtkProgressBar* to_GtkProgressBar(GtkWidget* w) { return GTK_PROGRESS_BAR(w); }
static GtkFixed* to_GtkFixed(GtkWidget* w) { return GTK_FIXED(w); }
static GtkCheckMenuItem* to_GtkCheckMenuItem(GtkWidget* w) { return GTK_CHECK_MENU_ITEM(w); }
static GtkRadioMenuItem* to_GtkRadioMenuItem(GtkWidget* w) { return GTK_RADIO_MENU_ITEM(w); }
static GtkFileFilter* to_GtkFileFilter(gpointer p) { return GTK_FILE_FILTER(p); }

#endif
