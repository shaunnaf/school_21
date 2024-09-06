-- Comment on the table
COMMENT ON TABLE person_discounts IS 'Эта таблица хранит информацию о скидках для каждого человека в каждой пиццерии.';

-- Comment on the person_id column
COMMENT ON COLUMN person_discounts.person_id IS 'Идентификатор человека, получающего скидку.';

-- Comment on the pizzeria_id column
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Идентификатор пиццерии, где действует скидка.';

-- Comment on the discount column
COMMENT ON COLUMN person_discounts.discount IS 'Процент скидки, который получает человек в указанной пиццерии.';
